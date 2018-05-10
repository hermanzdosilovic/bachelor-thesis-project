#pragma once

#include <istream>
#include <ostream>

namespace layouter
{

class OcrResult;

std::istream & operator>>( std::istream & is, OcrResult & ocrResult );
std::ostream & operator<<( std::ostream & os, OcrResult const & ocrResult );

}

