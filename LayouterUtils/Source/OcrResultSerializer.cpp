#include "OcrResultSerializer.hpp"

#include <OcrResult.hpp>

#include <nlohmann/json.hpp>

#include <fstream>
#include <iterator>
#include <cstdint>

namespace layouter
{

std::istream & operator>>( std::istream & is, OcrResult & ocrResult )
{
    nlohmann::json json;
    is >> json;

    nlohmann::json & jsonLineChars{
      json[ "ocr_result" ][ "blocks" ][ 0 ][ "lines" ][ 0 ][ "chars" ]
    };

    OcrResult::Line ocrResultLine;

    for
    (
        auto line{ std::begin( jsonLineChars ) }, lineEnd{ std::end( jsonLineChars ) };
        line != lineEnd;
        std::advance( line, 1 )
    )
    {
        ocrResultLine.emplace_back
        (
            line->at( "value" ),
            line->at( "bounding_box" )[ "x" ],
            line->at( "bounding_box" )[ "y" ],
            line->at( "bounding_box" )[ "width" ],
            line->at( "bounding_box" )[ "height" ]
        );
    }

    ocrResult.lines_.emplace_back( ocrResultLine );

    return is;
}


std::ostream & operator<<( std::ostream & os, OcrResult const & ocrResult )
{
    nlohmann::json json;

    auto & lines{ json[ "ocr_result" ][ "blocks" ][ 0 ][ "lines" ] };

    for ( auto ocrLine : ocrResult.lines_ )
    {
        nlohmann::json line;
        for ( auto ocrChar : ocrLine )
        {
            line[ "chars" ].push_back(
                {
                    { "value", static_cast< std::uint8_t >( ocrChar.value_ ) },
                    {
                        "bounding_box",
                        {
                            { "x", ocrChar.x_ },
                            { "y", ocrChar.y_ },
                            { "width", ocrChar.width_ },
                            { "height", ocrChar.height_ }
                        }
                    }
                }
            );
        }
        lines.push_back( line );
    }

    os << json;

    return os;
}

}
