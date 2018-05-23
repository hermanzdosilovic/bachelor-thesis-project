#include <Layouter/Layouter.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>
#include <String.hpp>

#include <cmdline.h>

#include <iostream>
#include <string>
#include <vector>
#include <limits>

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

void print( char const c, std::size_t const n, char const e )
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

    for ( auto const & inputEntry : dataset )
    {
        if ( !testCase.empty() && std::get< 0 >( inputEntry ) != testCase )
        {
            continue;
        }

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

        print( '-', 80, '\n' );
        std::cout << "Test case        : " << std::get< 0 >( inputEntry ) << '\n';
        std::cout << "Aligner Accuracy : " << alignerAccuracy << '\n';
        std::cout << "Spacer Accuracy  : " << spacerAccuracy << '\n';
        print( '-', 80, '\n' );
        std::cout << spacedString << '\n';
        print( '-', 80, '\n' );
        std::cout << '\n' << '\n' << '\n' << '\n';

        minAlignerAccuracy = std::min( minAlignerAccuracy, alignerAccuracy );
        maxAlignerAccuracy = std::max( maxAlignerAccuracy, alignerAccuracy );
        avgAlignerAccuracy += alignerAccuracy;

        minSpacerAccuracy = std::min( minSpacerAccuracy, spacerAccuracy );
        maxSpacerAccuracy = std::max( maxSpacerAccuracy, spacerAccuracy );
        avgSpacerAccuracy += spacerAccuracy;
    }

    avgSpacerAccuracy /= std::size( dataset );

    print( '-', 80, '\n' );
    std::cout << "Results" << '\n';
    print( '-', 80, '\n' );
    std::cout << "Min aligner accuracy: " << minAlignerAccuracy << '\n' <<
                 "Max aligner accuracy: " << maxAlignerAccuracy << '\n' <<
                 "Avg aligner accuracy: " << avgAlignerAccuracy << '\n' <<
                 "                    : "                       << '\n' <<
                 "Min spacer accuracy : " << minSpacerAccuracy  << '\n' <<
                 "Max spacer accuracy : " << maxSpacerAccuracy  << '\n' <<
                 "Avg spacer accuracy : " << avgSpacerAccuracy  << '\n';
    print( '-', 80, '\n' );

    return 0;
}
