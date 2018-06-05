#include "String.hpp"

#include <Utf8.hpp>

std::ostream & operator<<( std::ostream & os, layouter::wide_string const & wideString )
{
    os << layouter::Util::toUtf8( wideString );
    return os;
}


