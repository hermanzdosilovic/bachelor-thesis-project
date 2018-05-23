#include "AlignerTest.hpp"

#include "TestResult.hpp"

#include <Layouter/Aligner/MaxOverlapAligner.hpp>

#include <DatasetReader.hpp>
#include <Metric/EditDistanceMetric.hpp>

#include <spdlog/spdlog.h>

#include <catch.hpp>

namespace test::layouter::aligner
{

TEST_CASE( "max overlap aligner test on annotated Receipt", "[max overlap aligner]" )
{
    std::shared_ptr< spdlog::logger > console = spdlog::stdout_color_mt( "max overlap aligner" );

    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( "Receipt", "annotated" ) };

    Util::TestResult result = alignerTest
    (
        ::layouter::aligner::MaxOverlapAlignerParameter{ 0.13f, 1 },
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

    REQUIRE( result.satisfactoryAccuracy_ >= 0.47f );
    REQUIRE( result.maxAccuracy_ == 1.0f );
    REQUIRE( result.avgAccuracy_ >= 0.979f );
}

}
