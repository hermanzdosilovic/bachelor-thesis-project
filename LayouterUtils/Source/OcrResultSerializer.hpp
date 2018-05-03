#pragma once

#include <string_view>

namespace layouter
{

class OcrResult;

namespace Utils
{

OcrResult deserialize( std::string_view const & jsonFilePath );

}

}
