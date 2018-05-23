#pragma once

#include "Types.hpp"

namespace layouter
{

class OcrResult;

namespace spacer
{

class AvgRelativeDistanceSpacerParameter final
{
public:

    AvgRelativeDistanceSpacerParameter() noexcept = default;
    AvgRelativeDistanceSpacerParameter
    (
        value_t horizontalThreshold,
        value_t relativeDistanceThreshold
    ) :
        horizontalThreshold_{ horizontalThreshold },
        relativeDistanceThreshold_{ relativeDistanceThreshold } {};

    value_t horizontalThreshold_{ 3.0f };
    value_t relativeDistanceThreshold_{ 1.1f };
};

OcrResult space( AvgRelativeDistanceSpacerParameter const & parameter, OcrResult const & ocrResult );

}

}