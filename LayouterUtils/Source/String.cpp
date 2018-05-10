#include "String.hpp"

#include <sstream>

namespace layouter::Util
{

utf8_string to_utf8_string( wide_string const & wideString )
{
    std::basic_stringstream< utf8_string::value_type > sstream;
    for ( auto c : wideString )
    {
        sstream << static_cast< utf8_string::value_type >( c );
    }
    return sstream.str();
}

}

std::ostream & operator<<( std::ostream & os, layouter::wide_string const & wideString )
{
    os << layouter::Util::to_utf8_string( wideString );
    return os;
}


