#include "SpacerTest.hpp"

#include <Layouter/Aligner/MaxOverlapAligner.hpp>
#include <Layouter/Spacer/AvgCharWidthSpacer.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>

#include <spdlog/spdlog.h>

#include <catch.hpp>

namespace test::layouter::spacer
{

TEST_CASE( "average char width spacer test on annotated Receipt", "[average char width spacer]" )
{
    std::shared_ptr< spdlog::logger > console = spdlog::stdout_color_mt( "average char width spacer" );

    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( "Receipt", "annotated" ) };

    Util::TestResult result = spacerTest
    (
        ::layouter::aligner::MaxOverlapAlignerParameter{ 0.13f, 1 },
        ::layouter::spacer::AvgCharWidthSpacerParameter{ 0.44f },
        [] ( ::layouter::wide_string const & source, ::layouter::wide_string const & target ) -> float
        {
            return ::layouter::Metric::editDistance( source, target );
        },
        dataset,
        1.0f
    );

    console->info
    (
        "satisfactoryAccuracy = {}; minAccuracy = {}; maxAccuracy = {}; avgAccuracy = {}",
        result.satisfactoryAccuracy_, result.minAccuracy_, result.maxAccuracy_, result.avgAccuracy_
    );

    REQUIRE( result.satisfactoryAccuracy_ >= 0.02f );
    REQUIRE( result.maxAccuracy_ == 1.0f );
    REQUIRE( result.avgAccuracy_ >= 0.959f );
}

}