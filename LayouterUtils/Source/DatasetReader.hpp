#pragma once

#include "Types.hpp"

#include <vector>
#include <string_view>
#include <utility>
#include <map>

namespace layouter
{

class OcrResult;

using DataEntry = std::pair< OcrResult, wide_string >;
using Dataset = std::vector< DataEntry >;

namespace Util
{

Dataset readDataset( std::string const & datasetPath, std::string const & useCase, std::string const & model );
Dataset readDataset( std::string const & useCase, std::string const & model );

std::map< std::string, OcrResult > readInputs( std::string const & datasetPath, std::string const & useCase, std::string const & model );
std::map< std::string, OcrResult > readInputs( std::string const & useCase, std::string const & model );

std::map< std::string, wide_string > readOutputs( std::string const & datasetPath, std::string const & useCase, std::string const & model );
std::map< std::string, wide_string > readOutputs( std::string const & useCase, std::string const & model );

}

}
