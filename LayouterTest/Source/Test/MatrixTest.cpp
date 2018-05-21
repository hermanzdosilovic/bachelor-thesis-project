#include "Matrix.hpp"

#include <catch.hpp>

#include <stddef.h>

namespace test::layouter::Util
{

SCENARIO( "matrix can have arbitrary size", "[matrix]" )
{
    GIVEN( "arbitrary size matrix" )
    {
        constexpr std::size_t rows{ 5 };
        constexpr std::size_t cols{ 3 };

        Util::Matrix const m{ rows, cols };

        WHEN( "the size is checked" )
        {
            std::size_t const & matrixRows{ m.rows() };
            std::size_t const & matrixCols{ m.cols() };

            THEN( "the size is the same as when matrix was defined" )
            {
                REQUIRE( matrixRows == rows );
                REQUIRE( matrixCols == cols );
            }
        }
    }
}

SCENARIO( "inserting elements to matrix", "[matrix]" )
{
    GIVEN( "matrix of doubles" )
    {
        Util::Matrix m{ 3, 2 };

        WHEN( "element is inserted at position (0, 0)" )
        {
            constexpr double value{ 10.0f };
            m( 0, 0 ) = value;

            THEN( "element can be accessed" )
            {
                REQUIRE( m( 0, 0 ) == value );
            }
        }

        WHEN( "element is inserted at position (0, 1)" )
        {
            constexpr double value{ 5.0f };
            m( 0, 1 ) = value;

            THEN( "element can be accessed" )
            {
                REQUIRE( m( 0, 1 ) == value );
            }
        }

        WHEN( "element is inserted at every position" )
        {
            for ( std::size_t i{ 0 }; i < m.rows(); ++i )
            {
                for ( std::size_t j{ 0 }; j < m.cols(); ++j )
                {
                    m( i, j ) = 10 * ( i * m.cols() + j );
                }
            }

            THEN( "every can be accessed" )
            {

                for ( std::size_t i{ 0 }; i < m.rows(); ++i )
                {
                    for ( std::size_t j{ 0 }; j < m.cols(); ++j )
                    {
                        REQUIRE( m( i, j ) == 10 * ( i * m.cols() + j ) );
                    }
                }
            }
        }
    }
}

}
