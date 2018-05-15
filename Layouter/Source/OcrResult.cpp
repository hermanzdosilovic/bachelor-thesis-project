#include "OcrResult.hpp"

#include <sstream>

namespace layouter
{

wide_string OcrResult::toString()
{
    std::basic_stringstream< wide_string::value_type > sstream;

    sstream << static_cast< wide_string::value_type  >( '\n' );
    for ( auto line : lines_ )
    {
        for ( auto ocrChar : line )
        {
            sstream << ocrChar.toString();
        }
        sstream << static_cast< wide_string::value_type >( '\n' );
    }

    return sstream.str();
}

}