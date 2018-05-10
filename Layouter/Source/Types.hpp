#pragma once

#include <string>

namespace layouter
{

using wide_char   = char32_t;
using wide_string = std::basic_string< wide_char >;

using utf8_char   = char;
using utf8_string = std::basic_string< utf8_char >;

using value_t = float;

}
