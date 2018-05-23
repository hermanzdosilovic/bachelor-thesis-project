#pragma once

#include "Types.hpp"

#include <vector>
#include <string_view>
#include <tuple>
#include <map>

namespace layouter
{

class OcrResult;

using DataEntry = std::tuple< std::string, OcrResult, wide_string >;
using Dataset   = std::vector< DataEntry >;

using DatasetInputs  = std::map< std::string, OcrResult >;

using DatasetOutputs = std::map< std::string, wide_string >;

namespace Util
{

Dataset readDataset( std::string const & datasetPath, std::string const & useCase, std::string const & model );
Dataset readDataset( std::string const & useCase, std::string const & model );

DatasetInputs readInputs( std::string const & datasetPath, std::string const & useCase, std::string const & model );
DatasetInputs readInputs( std::string const & useCase, std::string const & model );

DatasetOutputs readOutputs( std::string const & datasetPath, std::string const & useCase, std::string const & model );
DatasetOutputs readOutputs( std::string const & useCase, std::string const & model );

}

}
