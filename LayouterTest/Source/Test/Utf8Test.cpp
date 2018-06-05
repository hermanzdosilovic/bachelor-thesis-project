#include <Utf8.hpp>

#include <catch.hpp>

#include <string>

namespace test::layouter::Util
{

TEST_CASE( "single utf8 character test", "to_utf8 char test" )
{
    REQUIRE( ::layouter::Util::to_utf8( 72    ) == u8"\u0048" );
    REQUIRE( ::layouter::Util::to_utf8( 353   ) == u8"\u0161" );
    REQUIRE( ::layouter::Util::to_utf8( 490   ) == u8"\u01EA" );
    REQUIRE( ::layouter::Util::to_utf8( 984   ) == u8"\u03D8" );
    REQUIRE( ::layouter::Util::to_utf8( 3247  ) == u8"\u0CAF" );
    REQUIRE( ::layouter::Util::to_utf8( 12089 ) == u8"\u2F39" );
}

TEST_CASE( "fixed string to utf8 string test", "to_utf8 string test" )
{
    std::basic_string< char32_t > fixedString;
    fixedString += static_cast< char32_t >( 269 );
    fixedString += static_cast< char32_t >( 97  );
    fixedString += static_cast< char32_t >( 114 );
    fixedString += static_cast< char32_t >( 100 );
    fixedString += static_cast< char32_t >( 97  );
    fixedString += static_cast< char32_t >( 353 );

    REQUIRE( ::layouter::Util::to_utf8( fixedString ) == u8"čardaš" );
}

}

