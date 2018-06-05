#include <Layouter/Layouter.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>
#include <String.hpp>
#include <Utf8.hpp>

#include <cmdline.h>

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

void initializeCmdParser( cmdline::parser & parser )
{
    parser.add< std::string >
    (
        "aligner",
        'a',
        "aligner type: none, maxoverlap",
        false,
        "none",
         cmdline::oneof< std::string >
         (
            "none",
            "maxoverlap"
         )
    );

    parser.add< std::string >
    (
         "spacer",
         's',
         "spacer type: none, avgcharwidth, avgreldist, avgcenterdist",
         false,
         "none",
         cmdline::oneof< std::string >
         (
             "none",
             "avgcharwidth",
             "avgreldist",
             "avgcenterdist",
             "avgreldist,avgcenterdist"
         )
    );

    parser.add< std::string >( "use-case", 'u', "use case", true, "" );

    parser.add< std::string >( "model", 'm', "model", true, "" );

    parser.add< std::string >( "test-case", 't', "run only specific test case", false, "" );

    parser.add< std::string >( "dataset", 'd', "dataset path", false, "" );

    parser.add( "result-only", '\0', "output only result" );
}

layouter::AlignerVariant selectAligner( std::string const & aligner )
{
    if ( aligner == "maxoverlap" )
    {
        return layouter::aligner::MaxOverlapAlignerParameter{};
    }

    return layouter::aligner::NoneAlignerParameter{};
}

layouter::CompositeSpacerVariant selectSpacer( std::string const & spacer )
{
    if ( spacer == "avgcharwidth" )
    {
        return layouter::spacer::AvgCharWidthSpacerParameter{};
    }
    else if ( spacer == "avgreldist" )
    {
        return layouter::spacer::AvgRelativeDistanceSpacerParameter{};
    }
    else if ( spacer == "avgcenterdist" )
    {
        return layouter::spacer::AvgCharCenterDistanceSpacerParameter{};
    }
    else if ( spacer == "avgreldist,avgcenterdist" )
    {
        return std::vector< layouter::SpacerVariant >
        {
            layouter::spacer::AvgRelativeDistanceSpacerParameter{},
            layouter::spacer::AvgCharCenterDistanceSpacerParameter{}
        };
    }

    return layouter::spacer::NoneSpacerParameter{};
}

void print( char const c, std::size_t const n, char const e = '\n' )
{
    for ( std::size_t i{ 0 }; i < n; ++i )
    {
        std::cout << c;
    }
    std::cout << e;
}

int main( int argc, char ** argv )
{
    cmdline::parser parser;
    initializeCmdParser( parser );
    parser.parse_check( argc, argv );

    layouter::AlignerVariant const & alignerVariant{ selectAligner( parser.get< std::string >( "aligner" ) ) };
    layouter::CompositeSpacerVariant const & spacerVariant{ selectSpacer ( parser.get< std::string >( "spacer" ) ) };

    layouter::Dataset const & dataset
    {
        layouter::Util::readDataset
        (
            parser.get< std::string >( "dataset" ),
            parser.get< std::string >( "use-case" ),
            parser.get< std::string >( "model" )
        )
    };

    std::string const & testCase{ parser.get< std::string >( "test-case" ) };

    float minAlignerAccuracy{ std::numeric_limits< float >::max() };
    float maxAlignerAccuracy{ std::numeric_limits< float >::min() };
    float avgAlignerAccuracy{ 0.0f };

    float minSpacerAccuracy{ std::numeric_limits< float >::max() };
    float maxSpacerAccuracy{ std::numeric_limits< float >::min() };
    float avgSpacerAccuracy{ 0.0f };

    float alignerAccuracyResult[ 11 ] = { 0.0f };
    float spacerAccuracyResult[ 11 ] = { 0.0f };

    std::size_t realDatasetSize{ 0 };

    for ( auto const & inputEntry : dataset )
    {
        if ( !testCase.empty() && std::get< 0 >( inputEntry ) != testCase )
        {
            continue;
        }

        realDatasetSize++;

        layouter::wide_string const & expected{ std::get< 2 >( inputEntry ) };
        layouter::wide_string filtered;
        std::copy_if
        (
            std::begin( expected ),
            std::end  ( expected ),
            std::back_inserter( filtered ),
            []( layouter::wide_string::value_type const & c )
            {
                return c != static_cast< layouter::wide_string::value_type >( ' ' );
            }
        );

        layouter::OcrResult const & alignedResult{ layouter::aligner::align( alignerVariant, std::get< 1 > ( inputEntry ) ) };
        float alignerAccuracy{ layouter::Metric::editDistance( alignedResult.toString(), filtered ) };

        layouter::OcrResult const & spacedResult{ layouter::spacer::space( spacerVariant, alignedResult ) };
        auto const & spacedString{ spacedResult.toString() };
        float spacerAccuracy{ layouter::Metric::editDistance( spacedString, expected ) };


        if ( !parser.exist( "result-only" ) )
        {
            print( '-', 80 );
            std::cout << "Test case        | " << std::get< 0 >( inputEntry ) << '\n';
            std::cout << "Aligner Accuracy | " << alignerAccuracy << '\n';
            std::cout << "Spacer Accuracy  | " << spacerAccuracy << '\n';
            print( '-', 80 );
            std::cout << layouter::Util::to_utf8( spacedString ) << '\n';
            print( '-', 80 );
            std::cout << '\n' << '\n' << '\n' << '\n';
        }

        minAlignerAccuracy = std::min( minAlignerAccuracy, alignerAccuracy );
        maxAlignerAccuracy = std::max( maxAlignerAccuracy, alignerAccuracy );
        avgAlignerAccuracy += alignerAccuracy;

        minSpacerAccuracy = std::min( minSpacerAccuracy, spacerAccuracy );
        maxSpacerAccuracy = std::max( maxSpacerAccuracy, spacerAccuracy );
        avgSpacerAccuracy += spacerAccuracy;

        std::uint8_t const alignerRoundAccuracy{ static_cast< std::uint8_t >( std::floor( alignerAccuracy * 10.0f ) ) };
        std::uint8_t const spacerRoundAccuracy{ static_cast< std::uint8_t >( std::floor( spacerAccuracy * 10.0f ) ) };

        for ( std::uint8_t i{ 0 }; i <= alignerRoundAccuracy; ++i )
        {
            alignerAccuracyResult[ i ]++;
        }

        for ( std::uint8_t i{ 0 }; i <= spacerRoundAccuracy; ++i )
        {
            spacerAccuracyResult[ i ]++;
        }
    }

    avgAlignerAccuracy /= realDatasetSize;
    avgSpacerAccuracy  /= realDatasetSize;

    print( '-', 80 );
    std::cout << "Results" << '\n';
    print( '-', 80 );
    std::cout << "Dataset size         | " << realDatasetSize    << '\n' <<
                 "Min aligner accuracy | " << minAlignerAccuracy << '\n' <<
                 "Max aligner accuracy | " << maxAlignerAccuracy << '\n' <<
                 "Avg aligner accuracy | " << avgAlignerAccuracy << '\n' <<
                 "                     | "                       << '\n' <<
                 "Min spacer accuracy  | " << minSpacerAccuracy  << '\n' <<
                 "Max spacer accuracy  | " << maxSpacerAccuracy  << '\n' <<
                 "Avg spacer accuracy  | " << avgSpacerAccuracy  << '\n';

    std::cout << '\n' << "Aligner Results:" << '\n';
    for ( std::uint8_t i{ static_cast< std::uint8_t >( std::floor( minAlignerAccuracy * 10.0f ) ) } ; i < 11; ++i )
    {
        std::printf( "%3d%% >= %.2f\n", i * 10, alignerAccuracyResult[ i ] / realDatasetSize );
    }
    std::cout << '\n' << "Spacer Results:" << '\n';
    for ( std::uint8_t i{ static_cast< std::uint8_t >( std::floor( minSpacerAccuracy * 10.0f ) ) }; i < 11; ++i )
    {
        std::printf( "%3d%% >= %.2f\n", i * 10, spacerAccuracyResult[ i ] / realDatasetSize );
    }
    print( '-', 80 );

    return 0;
}
