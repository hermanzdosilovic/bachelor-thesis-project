#pragma once

#include "MaxOverlapAligner.hpp"
#include "NoneAligner.hpp"

namespace layouter
{

class OcrResult;

namespace aligner
{

template< typename AlignerType >
OcrResult align( AlignerType const & alignerType, OcrResult const & ocrResult )
{
    return align( alignerType, ocrResult );
}

}

}