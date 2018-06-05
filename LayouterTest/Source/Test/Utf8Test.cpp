#include <Utf8.hpp>

#include <catch.hpp>

#include <string>

namespace test::layouter::Util
{

TEST_CASE( "fixed string to utf8 string test", "to_utf8 string test" )
{
    std::basic_string< char32_t > fixedString;
    fixedString += static_cast< char32_t >( 269 );
    fixedString += static_cast< char32_t >( 97  );
    fixedString += static_cast< char32_t >( 114 );
    fixedString += static_cast< char32_t >( 100 );
    fixedString += static_cast< char32_t >( 97  );
    fixedString += static_cast< char32_t >( 353 );

    REQUIRE( ::layouter::Util::toUtf8( fixedString ) == u8"čardaš" );
}

TEST_CASE( "utf8 string to fixed width string test", "toFixedWidth test" )
{
    std::basic_string< char32_t > fixedString;
    fixedString += static_cast< char32_t >( 269 );
    fixedString += static_cast< char32_t >( 97  );
    fixedString += static_cast< char32_t >( 114 );
    fixedString += static_cast< char32_t >( 100 );
    fixedString += static_cast< char32_t >( 97  );
    fixedString += static_cast< char32_t >( 353 );

    REQUIRE( ::layouter::Util::toFixedWidth( u8"čardaš" ) == fixedString );
}

}

