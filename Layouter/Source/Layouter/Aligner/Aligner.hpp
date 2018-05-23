#pragma once

#include "MaxOverlapAligner.hpp"
#include "NoneAligner.hpp"
#include "OcrResult.hpp"

#include <variant>

namespace layouter
{

using AlignerVariant = std::variant< aligner::NoneAlignerParameter, aligner::MaxOverlapAlignerParameter >;

namespace aligner
{

OcrResult align( AlignerVariant const & alignerVariant, OcrResult const & ocrResult );

template< typename AlignerType >
OcrResult align( AlignerType const & alignerType, OcrResult const & ocrResult )
{
    return align( alignerType, ocrResult );
}

}

}