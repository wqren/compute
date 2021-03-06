//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

//[time_copy_example

#include <vector>
#include <cstdlib>
#include <iostream>

#include <boost/compute.hpp>

namespace compute = boost::compute;

int main()
{
    // get the default device
    compute::device gpu = compute::system::default_device();

    // create context for default device
    compute::context context(gpu);

    // create command queue with profiling enabled
    compute::command_queue queue(context,
                                 gpu,
                                 compute::command_queue::enable_profiling);

    // generate random data on the host
    std::vector<int> host_vector(100000);
    std::generate(host_vector.begin(), host_vector.end(), rand);

    // create a vector on the device
    compute::vector<int> device_vector(host_vector.size(), context);

    // copy data from the host to the device
    compute::future<void> future =
        compute::copy_async(
            host_vector.begin(),
            host_vector.end(),
            device_vector.begin(),
            queue
        );

    // wait for copy to finish
    future.wait();

    using compute::ulong_;

    // get elapsed time from event profiling information
    ulong_ start_time =
        future.get_event().get_profiling_info<ulong_>(
            compute::event::profiling_command_start
        );
    ulong_ end_time =
        future.get_event().get_profiling_info<ulong_>(
            compute::event::profiling_command_end
        );
    ulong_ elapsed = end_time - start_time;

    // print elapsed time in milliseconds
    std::cout << "time: " << elapsed / 1e6 << " ms" << std::endl;

    return 0;
}

//]
