#include "DatasetReader.hpp"
#include "OcrResultSerializer.hpp"

#include <OcrResult.hpp>

#include <dirent.h>
#include <iostream>
#include <fstream>

namespace layouter::Util
{

Dataset readDataset( std::string const & datasetPath, std::string const & useCase, std::string const & model )
{
    std::map< std::string, OcrResult > inputs{ readInputs( datasetPath, useCase, model ) };
    std::map< std::string, wide_string > outputs{ readOutputs( datasetPath, useCase, model ) };

    Dataset dataset;

    for ( auto const & inputEntry : inputs )
    {
        auto outputEntry{ outputs.find( inputEntry.first ) };
        if ( outputEntry != outputs.end() )
        {
            dataset.emplace_back( inputEntry.second, outputEntry->second );
        }
    }

    return dataset;
}

std::map< std::string, OcrResult > readInputs( std::string const & datasetPath, std::string const & useCase, std::string const & model )
{
    std::string const inputExtension{ "json" };

    std::string const useCaseModelInputPath{ datasetPath + "/Inputs/" + useCase + "/" + model };

    std::map< std::string, OcrResult > inputs;

    DIR * dir = opendir( useCaseModelInputPath.c_str() );
    struct dirent * dirEntry;

    while ( ( dirEntry = readdir( dir ) ) != nullptr )
    {
        std::string const jsonInputFilename{ dirEntry->d_name };
        std::string::size_type const & jsonOffset{ jsonInputFilename.rfind( inputExtension ) };
        if ( jsonOffset == std::string::npos || jsonInputFilename.size() - jsonOffset != inputExtension.size() )
        {
            continue;
        }

        std::string rawName{ jsonInputFilename.substr( 0, jsonOffset - 1 ) };

        std::ifstream jsonInputFile( useCaseModelInputPath + "/" + jsonInputFilename );
        if ( !jsonInputFile.is_open() )
        {
            continue;
        }

        OcrResult ocrResult;
        jsonInputFile >> ocrResult;

        inputs[ rawName ] = ocrResult;

        jsonInputFile.close();
    }

    closedir( dir );

    return inputs;
}

std::map< std::string, wide_string > readOutputs( std::string const & datasetPath, std::string const & useCase, std::string const & model )
{
    std::string const outputExtension{ "txt" };

    std::string const useCaseModelOutputPath{ datasetPath + "/Outputs/" + useCase + "/" + model };

    std::map< std::string, wide_string > outputs;

    DIR * dir = opendir( useCaseModelOutputPath.c_str() );
    struct dirent * dirEntry;

    while ( ( dirEntry = readdir( dir ) ) != nullptr )
    {
        std::string const txtOutputFilename{ dirEntry->d_name };
        std::string::size_type const & txtOffset{ txtOutputFilename.rfind( outputExtension ) };
        if ( txtOffset == std::string::npos || txtOutputFilename.size() - txtOffset != outputExtension.size() )
        {
            continue;
        }

        std::string rawName{ txtOutputFilename.substr( 0, txtOffset - 1 ) };

        std::ifstream txtOutputFile( useCaseModelOutputPath + "/" + txtOutputFilename );
        if ( !txtOutputFile.is_open() )
        {
            continue;
        }

        std::string tmpLine;
        wide_string txtOutput;
        while ( std::getline( txtOutputFile, tmpLine ) )
        {
            for ( auto c : tmpLine )
            {
                txtOutput += static_cast< wide_string::value_type >( c );
            }
            txtOutput += static_cast< wide_string::value_type >( '\n' );
        }

        outputs[ rawName ] = txtOutput;

        txtOutputFile.close();
    }

    closedir( dir );

    return outputs;
}

}
