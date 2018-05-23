#pragma once

#include "TestResult.hpp"

#include <OcrResult.hpp>
#include <Layouter/Aligner/Aligner.hpp>

#include <DatasetReader.hpp>

#include <algorithm>
#include <iterator>
#include <limits>

namespace test::layouter::aligner
{

template< typename AlignerType, typename Metric >
Util::TestResult alignerTest( AlignerType const & alignerType, Metric && metric, std::string const & useCase, std::string const & model, float const desiredAccuracy )
{
    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( useCase, model ) };
    return alignerTest( alignerType, metric, dataset, desiredAccuracy );
}

template< typename AlignerType, typename Metric >
Util::TestResult alignerTest( AlignerType const & alignerType, Metric && metric, ::layouter::Dataset const & dataset, float const desiredAccuracy )
{
    float satisfactoryAccuracy{ 0.0f };
    float minAccuracy{ std::numeric_limits< float >::max() };
    float maxAccuracy{ std::numeric_limits< float >::min() };
    float avgAccuracy{ 0.0f };

    for ( ::layouter::DataEntry const & dataEntry : dataset )
    {
        ::layouter::wide_string const & expected{ std::get< 2 >( dataEntry ) };
        ::layouter::wide_string filtered;
        std::copy_if
        (
            std::begin( expected ),
            std::end  ( expected ),
            std::back_inserter( filtered ),
            []( ::layouter::wide_string::value_type const & c )
            {
                return c != static_cast< ::layouter::wide_string::value_type >( ' ' );
            }
        );

        float accuracy{ static_cast< float >( metric( ::layouter::aligner::align( alignerType, std::get< 1 >( dataEntry ) ).toString(), filtered ) ) };
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