#include "MaxOverlapAligner.hpp"

#include "OcrResult.hpp"
#include "Types.hpp"

#include <algorithm>
#include <cstddef>

namespace layouter::aligner
{

OcrResult align( MaxOverlapAlignerParameter const & parameter, OcrResult const & ocrResult )
{
    OcrResult::Line characters;
    for ( OcrResult::Line const & line : ocrResult.lines_ )
    {
        for ( OcrChar const & character : line )
        {
            characters.push_back( character );
        }
    }

    OcrResult alignedOcrResult;
    OcrResult::Lines & lines{ alignedOcrResult.lines_ };

    auto const overlap
    {
        []( OcrChar const & leftChar, OcrChar const & rightChar ) -> value_t
        {
            return std::max
                   (
                       0.0f,
                       std::min( leftChar.y_ + leftChar.height_, rightChar.y_ + rightChar.height_ ) -
                       std::max( leftChar.y_                   , rightChar.y_                     )
                   ) /
                   std::min( leftChar.height_, rightChar.height_ );
        }
    };

    std::sort
    (
        std::begin( characters ),
        std::end  ( characters ),
        []( OcrChar const & leftChar, OcrChar const & rightChar ) -> bool
        {
            if ( leftChar.x_ == rightChar.x_ )
            {
                return leftChar.y_ < rightChar.y_;
            }
            return leftChar.x_ < rightChar.x_;
        }
    );

    for ( OcrChar const & ocrCharacter : characters )
    {
        value_t maxOverlap{ 0.0f };
        OcrResult::Line * pMaxOverlapLine{ nullptr };

        for ( OcrResult::Line & line : lines )
        {
            std::size_t numChecks{ std::min< std::size_t >( std::size( line ), parameter.overlapLookback_ ) };
            value_t lineOverlap{ 0.0f };
            auto lineIt{ std::end( line ) };

            while ( numChecks > 0 )
            {
                std::advance( lineIt, -1 );
                lineOverlap = std::max( lineOverlap, overlap( *lineIt, ocrCharacter ) );
                numChecks--;
            }

            if ( lineOverlap > maxOverlap )
            {
                maxOverlap      = lineOverlap;
                pMaxOverlapLine = &line;
            }
        }

        if ( maxOverlap > parameter.overlapThreshold_ )
        {
            pMaxOverlapLine->push_back( ocrCharacter );
        }
        else
        {
            lines.push_back( { ocrCharacter } );
        }
    }

    std::sort
    (
        std::begin( lines ),
        std::end  ( lines ),
        []( OcrResult::Line const & leftLine, OcrResult::Line const & rightLine ) -> bool
        {
            return leftLine[ 0 ].y_ < rightLine[ 0 ].y_;
        }
    );

    return alignedOcrResult;
}

}
