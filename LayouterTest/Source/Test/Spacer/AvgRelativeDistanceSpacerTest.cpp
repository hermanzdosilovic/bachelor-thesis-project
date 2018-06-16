#include "SpacerTest.hpp"

#include <Layouter/Aligner/MaxOverlapAligner.hpp>
#include <Layouter/Spacer/AvgRelativeDistanceSpacer.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>

#include <spdlog/spdlog.h>

#include <catch.hpp>

namespace test::layouter::spacer
{

TEST_CASE( "average relative distance spacer test on annotated Receipt", "[average relative distance spacer]" )
{
    std::shared_ptr< spdlog::logger > console = spdlog::stdout_color_mt( "average relative distance spacer" );

    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( "Receipt", "annotated" ) };

    Util::TestResult result = spacerTest
    (
        ::layouter::aligner::MaxOverlapAlignerParameter{ 0.13f, 1, 0.13f, 0.13f },
        ::layouter::spacer::AvgRelativeDistanceSpacerParameter{ 3.0f, 1.1f },
        [] ( ::layouter::wide_string const & source, ::layouter::wide_string const & target ) -> float
        {
            return ::layouter::Metric::editDistance( source, target );
        },
        dataset,
        0.99f
    );

    console->info
    (
        "satisfactoryAccuracy = {}; minAccuracy = {}; maxAccuracy = {}; avgAccuracy = {}",
        result.satisfactoryAccuracy_, result.minAccuracy_, result.maxAccuracy_, result.avgAccuracy_
    );

    REQUIRE( result.satisfactoryAccuracy_ >= 0.13f );
    REQUIRE( result.maxAccuracy_ >= 0.997f );
    REQUIRE( result.avgAccuracy_ >= 0.948f );
}

}
