#pragma once

#include "Types.hpp"

namespace layouter
{

class OcrResult;

namespace spacer
{

class AvgCharCenterDistanceSpacerParameter final
{
public:

    AvgCharCenterDistanceSpacerParameter() noexcept = default;
    AvgCharCenterDistanceSpacerParameter
    (
        value_t horizontalThreshold,
        value_t avgCenterDistanceThreshold
    ) :
        horizontalThreshold_{ horizontalThreshold },
        avgCenterDistanceThreshold_{ avgCenterDistanceThreshold } {};

    value_t horizontalThreshold_{ 3.0f };
    value_t avgCenterDistanceThreshold_{ 1.2f };
};

OcrResult space( AvgCharCenterDistanceSpacerParameter const & parameter, OcrResult const & ocrResult );

}

}