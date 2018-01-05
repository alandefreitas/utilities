//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_PARALLEL_UTILS_H
#define WPP_PARALLEL_UTILS_H

// External
#include "ThreadPool.h"

#define BOOST_THREAD_PROVIDES_FUTURE
#include <boost/compute.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/core.hpp>
#include <boost/timer/timer.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/lockfree/policies.hpp>
#include <boost/lockfree/queue.hpp>

// Internal
#include "container_helpers/container_overloads.h"
#include "stream/progress_bar.h"


namespace utl {
    using thread_pool = ThreadPool;
    namespace compute = boost::compute;

}

#endif //WPP_PARALLEL_UTILS_H
