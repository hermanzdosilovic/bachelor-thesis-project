#pragma once

#include "OcrResult.hpp"
#include "AvgCharCenterDistanceSpacer.hpp"
#include "AvgCharWidthSpacer.hpp"
#include "AvgRelativeDistanceSpacer.hpp"
#include "NoneSpacer.hpp"

#include <variant>

namespace layouter
{

using SpacerVariant = std::variant
       <
               spacer::NoneSpacerParameter,
               spacer::AvgCharWidthSpacerParameter,
               spacer::AvgRelativeDistanceSpacerParameter,
               spacer::AvgCharCenterDistanceSpacerParameter
       >;

namespace spacer
{

OcrResult space( SpacerVariant const & spacerVariant, OcrResult const & ocrResult );

template< typename SpacerType >
OcrResult space( SpacerType const & spacerType, OcrResult const & ocrResult )
{
    return space( spacerType, ocrResult );
}

}

}
