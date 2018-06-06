#include <Utf8.hpp>

#include <catch.hpp>

#include <string>

#include "Unicode.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <utility>

namespace test::layouter::Util
{

template< typename CharType >
std::pair< std::basic_string< CharType >, std::string > generateUnicodePair( std::size_t const len )
{
    static std::random_device randomDevice;
    static std::mt19937       generator{ randomDevice() };

    std::uint32_t const maxValue{ static_cast< std::uint32_t >( std::numeric_limits< CharType >::max() ) };
    auto const & last
    {
        std::upper_bound
        (
            std::begin( dosilovic::unicode::code_points ),
            std::end  ( dosilovic::unicode::code_points ),
            maxValue
        )
    };

    assert( last != std::begin( dosilovic::unicode::code_points ) );

    auto const & distance
    {
        std::distance
        (
            std::begin( dosilovic::unicode::code_points ),
            std::prev ( last )
        )
    };

    std::uniform_int_distribution< int > distribution( 0, static_cast< int >( distance ) );

    std::basic_stringstream< CharType > wide;
    std::stringstream utf8;

    for ( std::size_t i{ 0 }; i < len; ++i )
    {
        int const index{ distribution( generator ) };
        char32_t const code_point{ dosilovic::unicode::code_points[ index ] };

        assert( code_point <= maxValue );

        wide << static_cast< CharType >( code_point );
        utf8 << dosilovic::unicode::table.find( code_point )->second;
    }

    return { wide.str(), utf8.str() };
}

TEST_CASE( "random utf8 test", "testis" )
{
    for ( std::size_t i{ 0 }; i < 100000; ++i )
    {
        auto const & p{ generateUnicodePair< char32_t >( 10 ) };
        REQUIRE( ::layouter::Util::toUtf8( p.first ) == p.second );
        REQUIRE( ::layouter::Util::toFixedWidth( p.second ) == p.first );
    }
}

}

