#include "String.hpp"

#include <PetiteUtf8.hpp>

std::ostream & operator<<( std::ostream & os, layouter::wide_string const & wideString )
{
    os << petiteutf8::utf8::encode< layouter::wide_string::value_type >( wideString );
    return os;
}


