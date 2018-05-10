#pragma once

#include "OcrChar.hpp"

#include <vector>
#include <ostream>

namespace layouter
{

class OcrResult final
{
public:
    using Line  = std::vector< OcrChar >;
    using Lines = std::vector< Line >;

    OcrResult() = default;

    wide_string toString();

    Lines lines_;
};

}
