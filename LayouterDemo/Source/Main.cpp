#include <OcrResult.hpp>

#include <DatasetReader.hpp>
#include <OcrResultSerializer.hpp>
#include <String.hpp>

#include <iostream>
#include <Layouter/Layouter.hpp>

int main( int argc, char ** argv )
{
    std::map< std::string, layouter::OcrResult > inputs{ layouter::Util::readInputs( argv[ 1 ], "Receipt", "annotated" ) };
    for ( auto mapEntry : inputs )
    {
        std::cout << mapEntry.first << std::endl;
        layouter::OcrResult layoutedResult{ layouter::layout( layouter::aligner::NoneAlignerParameter{}, layouter::spacer::NoneSpacerParameter{}, mapEntry.second ) };
        std::cout << layoutedResult.toString() << std::endl;
    }

    return 0;
}
