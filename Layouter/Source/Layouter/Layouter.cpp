#include "Layouter.hpp"

namespace layouter
{

OcrResult layout( AlignerVariant const & alignerVariant, SpacerVariant const & spacerVariant, OcrResult const & ocrResult )
{
    OcrResult alignedResult
              {
                  std::visit
                  (
                      [ & ocrResult ] ( auto parameter )
                      {
                          return aligner::align( parameter, ocrResult );
                      },
                      alignerVariant
                  )
              };

    return std::visit
           (
               [ & alignedResult ] ( auto parameter )
               {
                   return spacer::space( parameter, alignedResult );
               },
               spacerVariant
           );
}

}
