#pragma once

#include "Types.hpp"

#include <cstddef>

namespace layouter
{

class OcrResult;

namespace aligner
{

class MaxOverlapAlignerParameter final
{
public:

    MaxOverlapAlignerParameter() noexcept = default;
    MaxOverlapAlignerParameter
    (
        value_t     overlapThreshold,
        std::size_t overlapLookback
    ) :
        overlapThreshold_{ overlapThreshold },
        overlapLookback_{ overlapLookback } {};

    value_t     overlapThreshold_ = 0.1f;
    std::size_t overlapLookback_  = 1;
};

OcrResult align( MaxOverlapAlignerParameter const & parameter, OcrResult const & ocrResult );

}

}