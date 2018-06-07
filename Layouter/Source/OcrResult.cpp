#include "OcrResult.hpp"

#include <sstream>

namespace layouter
{

wide_string OcrResult::toString() const
{
    std::basic_stringstream< wide_string::value_type > sstream;

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
