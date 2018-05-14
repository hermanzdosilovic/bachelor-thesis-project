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
        layouter::OcrResult layoutedResult{ layouter::layout( layouter::aligner::MaxOverlapAlignerParameter{}, layouter::spacer::NoneSpacerParameter{}, mapEntry.second ) };
        std::cout << layoutedResult.toString() << std::endl;
        break;
    }

    return 0;
}
