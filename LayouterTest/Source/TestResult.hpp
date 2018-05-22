#pragma once

namespace test::layouter::Util
{

class TestResult final
{
public:

    TestResult
    (
        float satisfactoryAccuracy,
        float minAccuracy,
        float maxAccuracy,
        float avgAccuracy
    ) :
       satisfactoryAccuracy_{ satisfactoryAccuracy },
       minAccuracy_{ minAccuracy },
       maxAccuracy_{ maxAccuracy },
       avgAccuracy_{ avgAccuracy } {};

    float satisfactoryAccuracy_;
    float minAccuracy_;
    float maxAccuracy_;
    float avgAccuracy_;
};

}