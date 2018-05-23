#include "OcrChar.hpp"

namespace layouter
{

wide_string OcrChar::toString() const
{
    return { value_ };
}

}