#include <Layouter/Layouter.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>
#include <String.hpp>

#include <cmdline.h>

#include <iostream>
#include <string>

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
             "avgcenterdist"
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

layouter::SpacerVariant selectSpacer( std::string const & spacer )
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
    layouter::SpacerVariant  const & spacerVariant { selectSpacer ( parser.get< std::string >( "spacer"  ) ) };

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

    for ( auto const & inputEntry : dataset )
    {
        if ( !testCase.empty() && std::get< 0 >( inputEntry ) != testCase )
        {
            continue;
        }

        layouter::OcrResult const & layoutedResult{ layouter::layout( alignerVariant, spacerVariant, std::get< 1 >( inputEntry ) ) };
        auto const & layoutedString{ layoutedResult.toString() };

        print( '-', 80, '\n' );
        std::cout << "Test case: " << std::get< 0 >( inputEntry ) << '\n';
        std::cout << "Accuracy : " << layouter::Metric::editDistance( layoutedString, std::get< 2 >( inputEntry ) ) << '\n';
        print( '-', 80, '\n' );
        std::cout << layoutedResult.toString() << '\n';
        print( '-', 80, '\n' );
        std::cout << '\n' << '\n' << '\n' << '\n';
    }

    return 0;
}
