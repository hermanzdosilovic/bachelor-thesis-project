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
        std::size_t overlapLookback,
        value_t     positiveWeight,
        value_t     negativeWeight
    ) :
        overlapThreshold_{ overlapThreshold },
        overlapLookback_{ overlapLookback },
        positiveWeight_{ positiveWeight },
        negativeWeight_{ negativeWeight } {};

    value_t     overlapThreshold_{ 0.13f };
    std::size_t overlapLookback_{ 1 };
    value_t     positiveWeight_{ 0.13f };
    value_t     negativeWeight_{ 0.13f };
};

OcrResult align( MaxOverlapAlignerParameter const & parameter, OcrResult const & ocrResult );

}

}