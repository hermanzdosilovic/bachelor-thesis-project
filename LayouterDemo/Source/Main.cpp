#include <OcrResult.hpp>

#include <OcrResultSerializer.hpp>
#include <DatasetReader.hpp>
#include <String.hpp>

#include <iostream>

int main( int argc, char ** argv )
{
    layouter::Dataset const dataset{ layouter::Util::readDataset( argv[ 1 ], "Receipt", "annotated" ) };
    for ( layouter::DataEntry dataEntry : dataset )
    {
        std::cout << dataEntry.second << std::endl << std::endl;
    }

    return 0;
}
