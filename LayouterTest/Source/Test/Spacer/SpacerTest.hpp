#pragma once

#include "TestResult.hpp"

#include <OcrResult.hpp>
#include <Layouter/Aligner/Aligner.hpp>
#include <Layouter/Spacer/Spacer.hpp>

#include <DatasetReader.hpp>

#include <algorithm>
#include <limits>

namespace test::layouter::spacer
{

template< typename AlignerType, typename SpacerType, typename Metric >
Util::TestResult spacerTest( AlignerType const & alignerType, SpacerType const & spacerType, Metric && metric, std::string const & useCase, std::string const & model, float const desiredAccuracy )
{
    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( useCase, model ) };
    return spacerTest( alignerType, spacerType, metric, dataset, desiredAccuracy );
}

template< typename AlignerType, typename SpacerType, typename Metric >
Util::TestResult spacerTest( AlignerType const & alignerType, SpacerType const & spacerType, Metric && metric, ::layouter::Dataset const & dataset, float const desiredAccuracy )
{
    float satisfactoryAccuracy{ 0.0f };
    float minAccuracy{ std::numeric_limits< float >::max() };
    float maxAccuracy{ std::numeric_limits< float >::min() };
    float avgAccuracy{ 0.0f };

    for ( ::layouter::DataEntry const & dataEntry : dataset )
    {
        ::layouter::OcrResult alignedResult{ ::layouter::aligner::align( alignerType, std::get< 1 >( dataEntry ) ) };
        float accuracy{ static_cast< float >( metric( ::layouter::spacer::space( spacerType, alignedResult ).toString(), std::get< 2 >( dataEntry ) ) ) };
        if ( accuracy >= desiredAccuracy )
        {
            satisfactoryAccuracy++;
        }

        minAccuracy = std::min( minAccuracy, accuracy );
        maxAccuracy = std::max( maxAccuracy, accuracy );
        avgAccuracy += accuracy;
    }

    satisfactoryAccuracy /= std::size( dataset );
    avgAccuracy          /= std::size( dataset );

    return { satisfactoryAccuracy, minAccuracy, maxAccuracy, avgAccuracy };
}

}