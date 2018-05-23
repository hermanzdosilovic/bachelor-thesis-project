#include "Aligner.hpp"

namespace layouter::aligner
{

OcrResult align( AlignerVariant const & alignerVariant, OcrResult const & ocrResult )
{
    return std::visit
           (
               [ & ocrResult ] ( auto parameter )
               {
                   return align( parameter, ocrResult );
               },
               alignerVariant
           );
}

}
