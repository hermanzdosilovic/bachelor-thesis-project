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

    AvgCharWidthSpacerParameter() = default;

    value_t avgCharWidthThreshold_ = 0.44f;
};

OcrResult space( AvgCharWidthSpacerParameter const & parameter, OcrResult const & ocrResult );

}

}