#include "Utf8.hpp"

#include <cstddef>
#include <sstream>

namespace layouter::Util
{

std::string to_utf8( char32_t const c )
{
    std::stringstream sstream;
    if ( c < 0x80ul )
    {
        sstream << static_cast< char >( c );
    }
    else if ( c < 0x800ul )
    {
        sstream << static_cast< char >( 0xC0ul | ( ( c >> 6ul ) & 0x1Ful ) );
        sstream << static_cast< char >( 0x80ul | ( c & 0x3Ful ) );
    }
    else if ( c < 0x10000ul )
    {
        sstream << static_cast< char >( 0xE0ul | ( ( c >> 12ul ) & 0xFul  ) );
        sstream << static_cast< char >( 0x80ul | ( ( c >> 6ul  ) & 0x3Ful ) );
        sstream << static_cast< char >( 0x80ul | ( c & 0x3Ful ) );
    }
    else
    {
        sstream << static_cast< char >( 0xF0ul | ( ( c >> 18ul ) & 0x7ul  ) );
        sstream << static_cast< char >( 0x80ul | ( ( c >> 12ul ) & 0x3Ful ) );
        sstream << static_cast< char >( 0x80ul | ( ( c >> 6ul  ) & 0x3Ful ) );
        sstream << static_cast< char >( 0x80ul | ( c & 0x3Ful ) );
    }

    return sstream.str();
}

std::string to_utf8( std::basic_string< char32_t > const & s )
{
    std::stringstream sstream;
    for ( char32_t const & c : s )
    {
        sstream << to_utf8( c );
    }
    return sstream.str();
}

}
