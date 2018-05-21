#pragma once

#include <OcrResult.hpp>
#include <Layouter/Aligner/Aligner.hpp>

#include <DatasetReader.hpp>

#include <spdlog/spdlog.h>

#include <algorithm>
#include <limits>

namespace test::layouter::aligner
{

template< typename AlignerType, typename Metric >
float alignerTest( AlignerType const & alignerType, Metric && metric, std::string const & useCase, std::string const & model, float const desiredAccuracy )
{
    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( useCase, model ) };
    return alignerTest( alignerType, metric, dataset, desiredAccuracy );
}

template< typename AlignerType, typename Metric >
float alignerTest( AlignerType const & alignerType, Metric && metric, ::layouter::Dataset const & dataset, float const desiredAccuracy )
{
    std::shared_ptr< spdlog::logger > console = spdlog::get( "aligner test" );
    if ( console.get() == nullptr )
    {
        console = spdlog::stdout_color_mt( "aligner test" );
    }

    float satisfactoryAccuracy{ 0.0f };
    float minAccuracy{ std::numeric_limits< float >::max() };
    float maxAccuracy{ std::numeric_limits< float >::min() };
    float avgAccuracy{ 0.0f };

    for ( ::layouter::DataEntry const & dataEntry : dataset )
    {
        float accuracy{ static_cast< float >( metric( ::layouter::aligner::align( alignerType, dataEntry.first ).toString(), dataEntry.second ) ) };
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

    console->info
             (
                 "satisfactoryAccuracy = {}; minAccuracy = {}; maxAccuracy = {}; avgAccuracy = {}",
                 satisfactoryAccuracy, minAccuracy, maxAccuracy, avgAccuracy
             );

    return satisfactoryAccuracy;
}

}