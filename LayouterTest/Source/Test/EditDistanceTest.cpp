#include "EditDistance.hpp"

#include <catch.hpp>

namespace test
{

SCENARIO( "empty source and/or target", "[edit distance]" )
{
    GIVEN( "empty source" )
    {
        std::string const source{ "" };

        WHEN( "target is not empty" )
        {
            std::string const target{ "Lorem ipsum" };

            THEN( "edit distance is the same as target length" )
            {
                REQUIRE( Util::editDistance( source, target ) == target.length() );
            }
        }

        WHEN( "target is empty" )
        {
            std::string const target{ "" };

            THEN( "edit distance is 0" )
            {
                REQUIRE( Util::editDistance( source, target ) == 0 );
            }
        }
    }

    GIVEN( "empty target" )
    {
        std::string const target{ "" };

        WHEN( "source is not empty" )
        {
            std::string const source{ "Lorem ipsum" };

            THEN( "edit distance is the same as source length" )
            {
                REQUIRE( Util::editDistance( source, target ) == source.length() );
            }
        }

        WHEN( "source is empty" )
        {
            std::string const source{ "" };

            THEN( "edit distance is 0" )
            {
                REQUIRE( Util::editDistance( source, target ) == 0 );
            }
        }
    }
}

SCENARIO( "single operation needed", "[edit distance]" )
{
    WHEN( "source and target differentiate in one character" )
    {
        std::string const source{ "ab" };
        std::string const target{ "ac" };

        THEN( "only substitution is needed" )
        {
            REQUIRE( Util::editDistance( source, target ) == 1 );
        }
    }

    WHEN( "source is longer than target" )
    {
        std::string const source{ "ab" };
        std::string const target{ "a" };

        THEN( "only deletion is needed" )
        {
            REQUIRE( Util::editDistance( source, target ) == 1 );
        }
    }

    WHEN( "target is longer than source" )
    {
        std::string const source{ "a" };
        std::string const target{ "ab" };

        THEN( "only insertion is needed" )
        {
            REQUIRE( Util::editDistance( source, target ) == 1);
        }
    }
}

TEST_CASE( "source and target have common prefix", "[edit distance]" )
{
    std::string const source{ "aaaaBBefg" };
    std::string const target{ "aaaaCBeg" };

    THEN( "edit distance is the distance between strings without prefixes" )
    {
        std::string const & sourceSubstr{ source.substr( 4 ) };
        std::string const & targetSubstr{ target.substr( 4 ) };

        REQUIRE( Util::editDistance( source, target ) == Util::editDistance( sourceSubstr, targetSubstr ) );
    }
}

TEST_CASE( "arbitrary source and target" )
{
    /* Ground truth: https://planetcalc.com/1721/ */

    REQUIRE( Util::editDistance< std::string >( "brown", "green" ) == 3 );
    REQUIRE( Util::editDistance< std::string >( "trainee", "brown" ) == 5 );

    REQUIRE( Util::editDistance< std::string >( "id126u1CNWtboe1UQisM", "euw2hZELHcw1OPx" ) == 18 );
    REQUIRE( Util::editDistance< std::string >( "gsO2SFi43yhRu4THn33z", "aHe5fCJwMWP6DAfqaq0p" ) == 20 );

    REQUIRE( Util::editDistance< std::string >( "ab", "a\nb" ) == 1 );
    REQUIRE( Util::editDistance< std::string >( "abcdefg", "abc\nd\nefg" ) == 2 );
    REQUIRE( Util::editDistance< std::string >( "abc\ndefg", "abc\nd\nefg" ) == 1 );
}

}
