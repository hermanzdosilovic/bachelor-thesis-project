#include "Spacer.hpp"

namespace layouter::spacer
{

OcrResult space( SpacerVariant const & spacerVariant, OcrResult const & ocrResult )
{
    return std::visit
           (
               [ & ocrResult ] ( auto parameter )
               {
                   return space( parameter, ocrResult );
               },
               spacerVariant
           );
}

}
