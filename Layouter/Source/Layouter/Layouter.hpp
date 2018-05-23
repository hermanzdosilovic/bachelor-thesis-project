#pragma once

#include "OcrResult.hpp"
#include "Aligner/Aligner.hpp"
#include "Spacer/Spacer.hpp"

#include <variant>

namespace layouter
{

using AlignerVariant = std::variant< aligner::NoneAlignerParameter, aligner::MaxOverlapAlignerParameter >;

using SpacerVariant = std::variant
                      <
                          spacer::NoneSpacerParameter,
                          spacer::AvgCharWidthSpacerParameter,
                          spacer::AvgRelativeDistanceSpacerParameter,
                          spacer::AvgCharCenterDistanceSpacerParameter
                      >;

OcrResult layout( AlignerVariant const & alignerVariant, SpacerVariant const & spacerVariant, OcrResult const & ocrResult );

template< typename AlignerType, typename SpacerType >
OcrResult layout( AlignerType const & alignerType, SpacerType const & spacerType, OcrResult const & ocrResult )
{
    return spacer::space( spacerType, aligner::align( alignerType, ocrResult ) );
}

}