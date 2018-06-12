#include "Statistics.hpp"

#include <cstddef>

float median( std::vector< float > const & values )
{
    std::size_t n{ values.size() };
    std::size_t i{ n / 2 };

    if ( n % 2 != 0 )
    {
        return values[ i ];
    }

    return ( values[ i ] + values[ i - 1 ] ) / 2.0f;
}

float mean( std::vector< float > const & values )
{
    float avg{ 0.0f };
    for ( float const & v : values )
    {
        avg += v;
    }
    return avg / values.size();
}

