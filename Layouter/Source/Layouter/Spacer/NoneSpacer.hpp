#pragma once

namespace layouter
{

class OcrResult;

namespace spacer
{

class NoneSpacerParameter final {};

OcrResult space( NoneSpacerParameter const & parameter, OcrResult const & ocrResult );

}

}