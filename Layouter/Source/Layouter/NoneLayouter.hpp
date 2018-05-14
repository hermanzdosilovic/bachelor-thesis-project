#pragma once

namespace layouter
{

class OcrResult;

class NoneLayouterParameter final {};

OcrResult layout( NoneLayouterParameter const & parameter, OcrResult const & ocrResult );

}