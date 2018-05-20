#include "AlignerTest.hpp"

#include "Metric/EditDistanceMetric.hpp"

#include <Layouter/Aligner/MaxOverlapAligner.hpp>

#include <DatasetReader.hpp>

#include <catch.hpp>

namespace test::aligner
{

TEST_CASE( "max overlap aligner test on annotated Receipt", "[max overlap aligner]" )
{
    layouter::Dataset const & dataset{ layouter::Util::readDataset( std::filesystem::current_path().parent_path().string() + "/test-data", "Receipt", "annotated" ) };

    REQUIRE
    (
        alignerTest
        (
            layouter::aligner::MaxOverlapAlignerParameter{},
            [] ( layouter::wide_string const & source, layouter::wide_string const & target ) -> float
            {
                return Metric::editDistance( source, target );
            },
            dataset,
            0.85f
        )
        >= 0.58f
    );

    REQUIRE
    (
        alignerTest
        (
            layouter::aligner::MaxOverlapAlignerParameter{},
            [] ( layouter::wide_string const & source, layouter::wide_string const & target ) -> float
            {
                return Metric::editDistance( source, target );
            },
            dataset,
            0.9f
        )
        >= 0.1f
    );
}

}
