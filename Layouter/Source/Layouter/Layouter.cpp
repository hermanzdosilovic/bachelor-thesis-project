#include "Layouter.hpp"

namespace layouter
{

OcrResult layout( AlignerVariant const & alignerVariant, SpacerVariant const & spacerVariant, OcrResult const & ocrResult )
{
    OcrResult const & alignedResult{ aligner::align( alignerVariant, ocrResult ) };
    return spacer::space( spacerVariant, alignedResult );
}

}
