#pragma once

#include "Aligner/MaxOverlapAligner.hpp"
#include "Aligner/NoneAligner.hpp"
#include "OcrResult.hpp"
#include "Spacer/AvgCharWidthSpacer.hpp"
#include "Spacer/NoneSpacer.hpp"

#include <variant>

namespace layouter
{

using AlignerVariant = std::variant< aligner::NoneAlignerParameter, aligner::MaxOverlapAlignerParameter >;

using SpacerVariant = std::variant< spacer::NoneSpacerParameter, spacer::AvgCharWidthSpacerParameter >;

OcrResult layout( AlignerVariant const & alignerVariant, SpacerVariant const & spacerVariant, OcrResult const & ocrResult );

template< typename AlignerType, typename SpacerType >
OcrResult layout( AlignerType const & alignerType, SpacerType const & spacerType, OcrResult const & ocrResult )
{
    return spacer::space( spacerType, aligner::align( alignerType, ocrResult ) );
}

}