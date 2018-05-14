#pragma once

namespace layouter
{

class OcrResult;

namespace aligner
{

class NoneAlignerParameter final {};

OcrResult align( NoneAlignerParameter const & paramter, OcrResult const & ocrResult );

}

}