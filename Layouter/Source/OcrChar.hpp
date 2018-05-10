#pragma once

#include "Types.hpp"

#include <ostream>

namespace layouter
{

class OcrChar final
{
public:

    OcrChar
    (
        wide_char const value,
        value_t   const x,
        value_t   const y,
        value_t   const width,
        value_t   const height
    ) :
        value_{ value },
        x_{ x },
        y_{ y },
        width_{ width },
        height_{ height } {};

    wide_string toString();

    wide_char value_;
    value_t   x_;
    value_t   y_;
    value_t   width_;
    value_t   height_;
};

}
