#pragma once

#include "Types.hpp"

namespace layouter
{

class OcrResult;

namespace aligner
{

class MaxOverlapAlignerParameter final
{
public:

    MaxOverlapAlignerParameter() = default;

    value_t overlapThreshold_ = 0.1f;
    value_t overlapLookback_  = 1;
};

OcrResult align( MaxOverlapAlignerParameter const & parameter, OcrResult const & ocrResult );

}

}