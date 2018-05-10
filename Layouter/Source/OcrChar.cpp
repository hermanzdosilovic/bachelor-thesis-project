#include "OcrChar.hpp"

namespace layouter
{

wide_string OcrChar::toString()
{
    return { value_ };
}

}