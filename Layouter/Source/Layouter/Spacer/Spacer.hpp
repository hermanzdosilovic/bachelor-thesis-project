#pragma once

#include "AvgCharWidthSpacer.hpp"
#include "NoneSpacer.hpp"

namespace layouter
{

class OcrResult;

namespace spacer
{

template< typename SpacerType >
OcrResult space( SpacerType const & spacerType, OcrResult const & ocrResult )
{
    return space( spacerType, ocrResult );
}

}

}
