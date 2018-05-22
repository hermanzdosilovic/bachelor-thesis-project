#include "AlignerTest.hpp"

#include "Metric/EditDistanceMetric.hpp"

#include <Layouter/Aligner/MaxOverlapAligner.hpp>

#include <DatasetReader.hpp>

#include <catch.hpp>

namespace test::layouter::aligner
{

TEST_CASE( "max overlap aligner test on annotated Receipt", "[max overlap aligner]" )
{
    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( "Receipt", "annotated" ) };

    REQUIRE
    (
        alignerTest
        (
            ::layouter::aligner::MaxOverlapAlignerParameter{ 0.1f, 1 },
            [] ( ::layouter::wide_string const & source, ::layouter::wide_string const & target ) -> float
            {
                return Metric::editDistance( source, target );
            },
            dataset,
            0.85f
        ).satisfactoryAccuracy_
        >= 0.58f
    );

    REQUIRE
    (
        alignerTest
        (
            ::layouter::aligner::MaxOverlapAlignerParameter{ 0.1f, 1 },
            [] ( ::layouter::wide_string const & source, ::layouter::wide_string const & target ) -> float
            {
                return Metric::editDistance( source, target );
            },
            dataset,
            0.9f
        ).satisfactoryAccuracy_
        >= 0.1f
    );
}

}
