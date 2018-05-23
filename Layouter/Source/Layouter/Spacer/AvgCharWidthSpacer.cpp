#include "AvgCharWidthSpacer.hpp"

#include "OcrResult.hpp"
#include "Types.hpp"

namespace layouter::spacer
{

OcrResult space( AvgCharWidthSpacerParameter const & parameter, OcrResult const & ocrResult )
{
    OcrResult spacedResult;
    spacedResult.lines_ = ocrResult.lines_;

    for ( OcrResult::Line & line : spacedResult.lines_ )
    {
        value_t avgCharWidth{ 0.0f };
        for ( OcrChar const & c : line )
        {
            avgCharWidth += c.width_;
        }
        avgCharWidth /= std::size( line );

        value_t const newWordThreshold{ avgCharWidth * parameter.avgCharWidthThreshold_ };

        for
        (
            auto prevCharIt{ std::begin( line ) }, nextCharIt{ std::next( std::begin( line ) ) };
            nextCharIt != std::end( line );
            std::advance( prevCharIt, 1 ), std::advance( nextCharIt, 1 )
        )
        {
            if
            (
                prevCharIt->value_ == static_cast< wide_char >( ' ' ) ||
                nextCharIt->value_ == static_cast< wide_char >( ' ' )
            )
            {
                continue;
            }

            value_t const distance{ nextCharIt->x_ - ( prevCharIt->x_ + prevCharIt->width_ ) };
            if ( distance > newWordThreshold )
            {
                prevCharIt = line.emplace
                                  (
                                      nextCharIt,
                                      static_cast< wide_char >( ' ' ),
                                      prevCharIt->x_ + prevCharIt->width_,
                                      prevCharIt->y_,
                                      distance,
                                      prevCharIt->height_
                                  );
                nextCharIt = std::next( prevCharIt );
            }
        }
    }

    return spacedResult;
}

}