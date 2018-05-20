#pragma once

#include "EditDistance.hpp"

namespace test::Metric
{

template< typename StringType >
float editDistance( StringType const & source, StringType const & target )
{
    return 1.0f -
           test::Util::editDistance( source, target ) /
           static_cast< float >( test::Util::worstCaseEditDistance( source, target ) );
}

}