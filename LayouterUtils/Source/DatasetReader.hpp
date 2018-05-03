#pragma once

#include "Types.hpp"

#include <vector>
#include <string_view>

namespace layouter
{

class OcrResult;

namespace Util
{

std::vector< std::pair< OcrResult, layouter::wide_string > > readDataset( std::string_view const & useCase, std::string_view const & model );

}

}
