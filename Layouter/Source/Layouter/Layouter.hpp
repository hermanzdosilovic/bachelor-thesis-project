#pragma once

#include "OcrResult.hpp"
#include "Aligner/Aligner.hpp"
#include "Spacer/Spacer.hpp"

namespace layouter
{

OcrResult layout( AlignerVariant const & alignerVariant, SpacerVariant const & spacerVariant, OcrResult const & ocrResult );

template< typename AlignerType, typename SpacerType >
OcrResult layout( AlignerType const & alignerType, SpacerType const & spacerType, OcrResult const & ocrResult )
{
    return spacer::space( spacerType, aligner::align( alignerType, ocrResult ) );
}

}