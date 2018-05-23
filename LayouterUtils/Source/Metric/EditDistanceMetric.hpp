#pragma once

#include "EditDistance.hpp"

namespace layouter::Metric
{

template< typename StringType >
float editDistance( StringType const & source, StringType const & target )
{
    return 1.0f -
           Util::editDistance( source, target ) /
           static_cast< float >( Util::worstCaseEditDistance( source, target ) );
}

}