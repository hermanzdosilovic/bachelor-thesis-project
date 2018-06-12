#include "Statistics.hpp"

#include <Layouter/Layouter.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>
#include <String.hpp>

#include <cmdline.h>

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

    std::string const & useCase{ parser.get< std::string >( "use-case" ) };
    std::string const & model  { parser.get< std::string >( "model"    ) };
    std::string const & aligner{ parser.get< std::string >( "aligner"  ) };
    std::string const & spacer { parser.get< std::string >( "spacer"   ) };

    layouter::AlignerVariant const & alignerVariant{ selectAligner( aligner ) };
    layouter::CompositeSpacerVariant const & spacerVariant{ selectSpacer ( spacer ) };

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


        if ( !parser.exist( "result-only" ) )
        {
            print( '-', 80 );
            std::cout << "Test case        | " << std::get< 0 >( inputEntry ) << '\n';
            std::cout << "Aligner Accuracy | " << alignerAccuracy << '\n';
            std::cout << "Spacer Accuracy  | " << spacerAccuracy << '\n';
            print( '-', 80 );
            std::cout << spacedString << '\n';
            print( '-', 80 );
            std::cout << '\n' << '\n' << '\n' << '\n';
        }

        totalAlignerAccuracy.push_back( alignerAccuracy );
        totalSpacerAccuracy.push_back( spacerAccuracy );
    }

    std::sort( totalAlignerAccuracy.begin(), totalAlignerAccuracy.end() );
    std::sort( totalSpacerAccuracy.begin(), totalSpacerAccuracy.end() );

    std::vector< float > alignerMedianVector;
    float alignerMedian{ median( totalAlignerAccuracy ) };
    for ( auto const & v : totalAlignerAccuracy )
    {
        alignerMedianVector.push_back( alignerMedian );
    }

    std::vector< float > alignerMeanVector;
    float alignerMean{ mean( totalAlignerAccuracy ) };
    for ( auto const & v : totalAlignerAccuracy )
    {
        alignerMeanVector.push_back( alignerMean );
    }

    std::vector< float > spacerMedianVector;
    float spacerMedian{ median( totalAlignerAccuracy ) };
    for ( auto const & v : totalSpacerAccuracy )
    {
        spacerMedianVector.push_back( spacerMedian );
    }

    std::vector< float > spacerMeanVector;
    float spacerMean{ mean( totalAlignerAccuracy ) };
    for ( auto const & v : totalSpacerAccuracy )
    {
        spacerMeanVector.push_back( spacerMean );
    }

#ifdef LAYOUTERDEMO_USE_MATPLOTLIB
    matplotlibcpp::figure_size(1200, 780);
    matplotlibcpp::plot(totalSpacerAccuracy, "-");
    matplotlibcpp::named_plot("median", spacerMedianVector, "--");
    matplotlibcpp::named_plot("mean", spacerMeanVector, "--");
    matplotlibcpp::grid(true);
    matplotlibcpp::xlabel("example");
    matplotlibcpp::ylabel("accuracy");
    matplotlibcpp::legend();
    matplotlibcpp::title( useCase + " | " + model + " | " + aligner + " | " + spacer );
    matplotlibcpp::save("result.png");
#endif

    return 0;
}
