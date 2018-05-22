#include "SpacerTest.hpp"

#include "Metric/EditDistanceMetric.hpp"

#include <Layouter/Aligner/MaxOverlapAligner.hpp>
#include <Layouter/Spacer/AvgCharWidthSpacer.hpp>

#include <DatasetReader.hpp>

#include <catch.hpp>

namespace test::layouter::spacer
{

TEST_CASE( "average char width spacer test on annotated Receipt", "[average char width spacer]" )
{
    ::layouter::Dataset const & dataset{ ::layouter::Util::readDataset( "Receipt", "annotated" ) };

    REQUIRE
    (
        spacerTest
        (
            ::layouter::aligner::MaxOverlapAlignerParameter{ 0.1f, 1 },
            ::layouter::spacer::AvgCharWidthSpacerParameter{ 0.44f },
            [] ( ::layouter::wide_string const & source, ::layouter::wide_string const & target ) -> float
            {
                return Metric::editDistance( source, target );
            },
            dataset,
            0.95f
        ).satisfactoryAccuracy_
        >= 0.66f
    );

    REQUIRE
    (
        spacerTest
        (
            ::layouter::aligner::MaxOverlapAlignerParameter{ 0.1f, 1 },
            ::layouter::spacer::AvgCharWidthSpacerParameter{ 0.44f },
            [] ( ::layouter::wide_string const & source, ::layouter::wide_string const & target ) -> float
            {
                return Metric::editDistance( source, target );
            },
            dataset,
            0.99f
        ).satisfactoryAccuracy_
        >= 0.19f
    );
}

}