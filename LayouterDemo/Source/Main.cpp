#include <OcrResult.hpp>

#include <OcrResultSerializer.hpp>

#include <iostream>

int main( int argc, char ** argv )
{
    layouter::OcrResult result = layouter::Utils::deserialize( "Receipt" );
    return 0;
}
