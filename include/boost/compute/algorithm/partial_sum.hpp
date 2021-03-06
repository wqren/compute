//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/inclusive_scan.hpp>

namespace boost {
namespace compute {

template<class InputIterator, class OutputIterator>
inline OutputIterator
partial_sum(InputIterator first,
            InputIterator last,
            OutputIterator result,
            command_queue &queue = system::default_queue())
{
    return ::boost::compute::inclusive_scan(first, last, result, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP
