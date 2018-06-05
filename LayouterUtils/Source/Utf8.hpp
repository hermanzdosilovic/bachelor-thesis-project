#include <string>
#include <cstdint>
#include <vector>
#include <limits>

namespace layouter::Util
{
std::string to_utf8( char32_t const c );
std::string to_utf8( std::basic_string< char32_t > const & s );

std::basic_string< char32_t > toFixedWidth( std::string const & utf8String );

}