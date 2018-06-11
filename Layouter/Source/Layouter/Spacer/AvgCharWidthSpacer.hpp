#pragma once

#include "Types.hpp"

namespace layouter
{

class OcrResult;

namespace spacer
{

class AvgCharWidthSpacerParameter final
{
public:

    AvgCharWidthSpacerParameter() noexcept = default;
    AvgCharWidthSpacerParameter
    (
        value_t const avgCharWidthThreshold
    ) :
        avgCharWidthThreshold_{ avgCharWidthThreshold } {};

    value_t avgCharWidthThreshold_ = 0.8f;
};

OcrResult space( AvgCharWidthSpacerParameter const & parameter, OcrResult const & ocrResult );

}

}