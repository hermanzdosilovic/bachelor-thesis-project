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

using CompositeSpacerVariant = std::variant< SpacerVariant, std::vector< SpacerVariant > >;

namespace spacer
{

OcrResult space( SpacerVariant const & spacerVariant, OcrResult const & ocrResult );
OcrResult space( CompositeSpacerVariant const & compositeSpacerVariant, OcrResult const & ocrResult );
OcrResult space( std::vector< SpacerVariant > const & spacerVariants, OcrResult const & ocrResult );

template< typename SpacerType >
OcrResult space( SpacerType const & spacerType, OcrResult const & ocrResult )
{
    return space( spacerType, ocrResult );
}

}

}
