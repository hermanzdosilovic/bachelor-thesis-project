#pragma once

#include "OcrChar.hpp"

#include <vector>

namespace layouter
{

class OcrResult final
{
public:
    using Line  = std::vector< OcrChar >;
    using Lines = std::vector< Line >;

    OcrResult() = default;

    Lines lines_;
};

}
