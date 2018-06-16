#include "Statistics.hpp"

#include <Layouter/Layouter.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>
#include <String.hpp>

#include <cmdline.h>
#include <VariadicTable.h>

#ifdef LAYOUTERDEMO_USE_MATPLOTLIB
#include <matplotlibcpp.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

void initializeCmdParser( cmdline::parser & parser )
{
    parser.add< std::string >
    (
        "aligner", 'a', "aligner type: none, maxoverlap", false, "maxoverlap",
         cmdline::oneof< std::string >
         (
            "none",
            "maxoverlap"
         )
    );

    parser.add< std::string >
    (
         "spacer", 's', "spacer type: none, avgcharwidth, avgreldist, avgcenterdist", false, "avgcenterdist",
         cmdline::oneof< std::string >
         (
             "none",
             "avgcharwidth",
             "avgreldist",
             "avgcenterdist"
         )
    );

    parser.add< std::string >( "use-case", 'u', "use case", false, "Receipt" );
    parser.add< std::string >( "model", 'm', "model", false, "annotated" );
    parser.add< std::string >( "test-case", 't', "run only specific test case", false, "" );
    parser.add< std::string >( "dataset", 'd', "dataset path", false, "" );
    parser.add( "show-output", 0, "show layouter output" );

    parser.add< std::size_t >( "overlapLookback", 0, "c1 parameter in maxoverlap algorithm", false, 1 );
    parser.add< float >( "overlapThreshold", 0, "c2 parameter in maxoverlap algorithm", false, 0.13f );
    parser.add< float >( "negativeWeight", 0, "c3 parameter in maxoverlap algorithm", false, 0.13f );
    parser.add< float >( "positiveWeight", 0, "c4 parameter in maxoverlap algorithm", false, 0.13f );
    parser.add< float >( "avgCharWidthThreshold", 0, "c1 parameter in avgcharwidth algorithm", false, 0.8f );
    parser.add< float >( "horizontalThreshold", 0, "c1 parameter in avgreldist and avgcenterdist algorithm", false, 4.0f );
    parser.add< float >( "relativeDistanceThreshold", 0, "c2 parameter in avgreldist algorithm", false, 1.2f );
    parser.add< float >( "avgCenterDistanceThreshold", 0, "c2 parameter in avgcenterdist algorithm", false, 1.2f );
}

layouter::AlignerVariant selectAligner( std::string const & aligner, cmdline::parser const & parser )
{
    if ( aligner == "maxoverlap" )
    {
        return layouter::aligner::MaxOverlapAlignerParameter
        {
            parser.get< float >( "overlapThreshold" ),
            parser.get< std::size_t >( "overlapLookback" ),
            parser.get< float >( "positiveWeight" ),
            parser.get< float >( "negativeWeight" ),
        };
    }

    return layouter::aligner::NoneAlignerParameter{};
}

layouter::CompositeSpacerVariant selectSpacer( std::string const & spacer, cmdline::parser const & parser )
{
    if ( spacer == "avgcharwidth" )
    {
        return layouter::spacer::AvgCharWidthSpacerParameter
        {
            parser.get< float >( "avgCharWidthThreshold" )
        };
    }
    else if ( spacer == "avgreldist" )
    {
        return layouter::spacer::AvgRelativeDistanceSpacerParameter
        {
            parser.get< float >( "horizontalThreshold" ),
            parser.get< float >( "relativeDistanceThreshold" )
        };
    }
    else if ( spacer == "avgcenterdist" )
    {
        return layouter::spacer::AvgCharCenterDistanceSpacerParameter
        {
            parser.get< float >( "horizontalThreshold" ),
            parser.get< float >( "avgCenterDistanceThreshold" )
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

    std::string const & useCase{ parser.get< std::string >( "use-case" ) };
    std::string const & model  { parser.get< std::string >( "model"    ) };
    std::string const & aligner{ parser.get< std::string >( "aligner"  ) };
    std::string const & spacer { parser.get< std::string >( "spacer"   ) };

    layouter::AlignerVariant const & alignerVariant{ selectAligner( aligner, parser ) };
    layouter::CompositeSpacerVariant const & spacerVariant{ selectSpacer ( spacer, parser ) };

    layouter::Dataset const & dataset
    {
        layouter::Util::readDataset
        (
            parser.get< std::string >( "dataset" ),
            useCase,
            model
        )
    };

    std::string const & testCase{ parser.get< std::string >( "test-case" ) };

    std::vector< float > totalAlignerAccuracy;
    std::vector< float > totalSpacerAccuracy;

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


        if ( parser.exist( "show-output" ) )
        {
            print( '-', 80 );
            std::cout << "| Test case        | " << std::get< 0 >( inputEntry ) << '\n';
            std::cout << "| Aligner Accuracy | " << alignerAccuracy << '\n';
            std::cout << "| Spacer Accuracy  | " << spacerAccuracy << '\n';
            print( '-', 80 );
            std::cout << spacedString;
        }

        totalAlignerAccuracy.push_back( alignerAccuracy );
        totalSpacerAccuracy.push_back( spacerAccuracy );
    }

    std::sort( totalAlignerAccuracy.begin(), totalAlignerAccuracy.end() );
    std::sort( totalSpacerAccuracy.begin(), totalSpacerAccuracy.end() );

    float const alignerMin{ totalAlignerAccuracy[ 0 ] };
    float const alignerMax{ totalAlignerAccuracy.back() };
    float const alignerAvg{ mean( totalAlignerAccuracy ) };
    float const alignerMed{ median( totalAlignerAccuracy ) };
    float const alignerTop
    {
        static_cast< float >( std::count( totalAlignerAccuracy.begin(), totalAlignerAccuracy.end(), alignerMax ) ) /
        totalAlignerAccuracy.size()
    };

    float const spacerMin{ totalSpacerAccuracy[ 0 ] };
    float const spacerMax{ totalSpacerAccuracy.back() };
    float const spacerAvg{ mean( totalSpacerAccuracy ) };
    float const spacerMed{ median( totalSpacerAccuracy ) };
    float const spacerTop
    {
        static_cast< float >( std::count( totalSpacerAccuracy.begin(), totalSpacerAccuracy.end(), spacerMax ) ) /
        totalSpacerAccuracy.size()
    };

    VariadicTable< std::string, float, float, float, float, float > table
    (
        { "", "   min   ", "   avg   ", "   med   ", "   max   ", "   top   " }
    );

    table.setColumnFormat
    (
        {
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED,
            VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED, VariadicTableColumnFormat::FIXED
        }
    );

    table.addRow( { "aligner", alignerMin, alignerAvg, alignerMed, alignerMax, alignerTop } );
    table.addRow( { "spacer", spacerMin, spacerAvg, spacerMed, spacerMax, spacerTop } );
    table.print( std::cout );

#ifdef LAYOUTERDEMO_USE_MATPLOTLIB
    std::string const title{ useCase + "-" + model + "-" + aligner + "-" + spacer };
    matplotlibcpp::figure_size( 1920, 1080 );
    matplotlibcpp::named_plot( "aligner fitness", totalAlignerAccuracy, "b.-" );
    matplotlibcpp::named_plot( "spacer fitness", totalSpacerAccuracy, "r.-" );
    matplotlibcpp::grid( true );
    matplotlibcpp::xlabel( "test case" );
    matplotlibcpp::ylabel( "fitness" );
    matplotlibcpp::legend();
    matplotlibcpp::title( title );
    matplotlibcpp::save( title + ".png" );
#endif

    return 0;
}
