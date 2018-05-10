#pragma once

#include <Types.hpp>

#include <ostream>

namespace layouter::Util
{

utf8_string to_utf8_string( wide_string const & wideString );

}

std::ostream & operator<<( std::ostream & os, layouter::wide_string const & wideString );
