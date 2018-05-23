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

OcrResult space( CompositeSpacerVariant const & compositeSpacerVariant, OcrResult const & ocrResult )
{
    return std::visit
           (
               [ & ocrResult ] ( auto parameter )
               {
                   return space( parameter, ocrResult );
               },
               compositeSpacerVariant
           );
}

OcrResult space( std::vector< SpacerVariant > const & spacerVariants, OcrResult const & ocrResult )
{
    OcrResult spacedResult{ ocrResult };
    for ( auto const & variant : spacerVariants )
    {
        spacedResult = space( variant, spacedResult );
    }
    return spacedResult;
}

}
