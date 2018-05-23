#include "AvgRelativeDistanceSpacer.hpp"

#include "OcrResult.hpp"
#include "OcrChar.hpp"
#include "Types.hpp"

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>

namespace layouter::spacer
{

OcrResult space( AvgRelativeDistanceSpacerParameter const & parameter, OcrResult const & ocrResult )
{
    OcrResult spacedResult;
    spacedResult.lines_ = ocrResult.lines_;

    auto distanceFunction
    {
        []( OcrChar const & left, OcrChar const & right ) -> value_t
        {
            return std::abs( ( right.x_ + right.width_ / 2.0f ) - ( left.x_ + left.width_ / 2.0f ) );
        }
    };

    std::map< wide_char, std::size_t > charMeasureCountTable;
    std::map< wide_char, value_t     > charTotalDistanceTable;

    for ( OcrResult::Line const & line : spacedResult.lines_ )
    {
        for ( std::size_t i{ 1 }; i < std::size( line ); ++i )
        {
            OcrChar const & leftChar { line[ i - 1 ] };
            OcrChar const & rightChar{ line[ i     ] };

            value_t const horizontalDistance{ distanceFunction( leftChar, rightChar ) };
            value_t const normalizedHorizontalDistance{ horizontalDistance / std::min( leftChar.width_, rightChar.width_ ) };

            if ( normalizedHorizontalDistance < parameter.horizontalThreshold_ )
            {
                charMeasureCountTable [ rightChar.value_ ]++;
                charTotalDistanceTable[ rightChar.value_ ] += horizontalDistance;
            }
        }
    }

    for ( OcrResult::Line & line : spacedResult.lines_ )
    {
        for
        (
            auto prevCharIt{ std::begin( line ) }, nextCharIt{ std::next( std::begin( line ) ) };
            nextCharIt != std::end( line );
            std::advance( prevCharIt, 1 ), std::advance( nextCharIt, 1 )
        )
        {
            value_t const distance{ distanceFunction( *prevCharIt, *nextCharIt ) };
            value_t const avgRelativeDistance
            {
                charTotalDistanceTable[ nextCharIt->value_ ] / std::max( charMeasureCountTable[ nextCharIt->value_ ], static_cast< std::size_t >( 1 ) )
            };

            if ( distance > avgRelativeDistance * parameter.relativeDistanceThreshold_ )
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
