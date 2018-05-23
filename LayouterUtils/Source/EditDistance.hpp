#pragma once

#include "Matrix.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace layouter::Util
{

template< typename StringType >
std::size_t editDistance( StringType const & source, StringType const & target )
{
    if ( source.length() == 0 )
    {
        return target.length();
    }
    else if ( target.length() == 0 )
    {
        return source.length();
    }

    Matrix d{ source.length() + 1, target.length() + 1 };

    for ( std::size_t i{ 0 }; i < d.rows(); ++i )
    {
        d( i, 0 ) = i;
    }

    for ( std::size_t j{ 0 }; j < d.cols(); ++j )
    {
        d( 0, j ) = j;
    }

    constexpr std::uint8_t insertionCost{ 1 };
    constexpr std::uint8_t deletionCost{ 1 };
    constexpr std::uint8_t substitutionCost{ 1 };

    for ( std::size_t i{ 1 }; i < d.rows(); ++i )
    {
        for ( std::size_t j{ 1 }; j < d.cols(); ++j )
        {
            d( i, j ) = std::min
            (
                std::min
                (
                    d( i - 1, j     ) + deletionCost,
                    d( i    , j - 1 ) + insertionCost
                ),
                d( i - 1, j - 1 ) + ( source[ i - 1 ] == target[ j - 1 ] ? 0 : substitutionCost )
            );
        }
    }

    return d( d.rows() - 1, d.cols() - 1 );
}

template< typename StringType >
inline std::size_t worstCaseEditDistance( StringType const & source, StringType const & target )
{
    return std::max( source.length(), target.length() );
}

}