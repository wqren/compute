//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#define BOOST_TEST_MODULE TestGet
#include <boost/test/unit_test.hpp>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/result_of.hpp>

#include <boost/compute/pair.hpp>
#include <boost/compute/tuple.hpp>
#include <boost/compute/types.hpp>
#include <boost/compute/functional/get.hpp>

namespace compute = boost::compute;

BOOST_AUTO_TEST_CASE(get_vector_result_type)
{
    BOOST_STATIC_ASSERT((
        boost::is_same<
            boost::tr1_result_of<
                compute::get<0>(compute::float4_)
            >::type,
            float
        >::value
    ));
    BOOST_STATIC_ASSERT((
        boost::is_same<
            boost::tr1_result_of<
                compute::get<1>(compute::int2_)
            >::type,
            int
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(get_pair_result_type)
{
    BOOST_STATIC_ASSERT((
        boost::is_same<
            boost::tr1_result_of<
                compute::get<0>(std::pair<int, float>)
            >::type,
            int
        >::value
    ));
    BOOST_STATIC_ASSERT((
        boost::is_same<
            boost::tr1_result_of<
                compute::get<1>(std::pair<compute::float2_, compute::char4_>)
            >::type,
            compute::char4_
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(get_tuple_result_type)
{
    BOOST_STATIC_ASSERT((
        boost::is_same<
            boost::tr1_result_of<
                compute::get<0>(boost::tuple<int, int, double>)
            >::type,
            int
        >::value
    ));
    BOOST_STATIC_ASSERT((
        boost::is_same<
            boost::tr1_result_of<
                compute::get<2>(boost::tuple<char, int, float>)
            >::type,
            float
        >::value
    ));
}
