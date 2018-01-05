//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_CONTAINER_UTILS_H
#define WPP_CONTAINER_UTILS_H

// External
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unconstrained_set_of.hpp>
#include <boost/bimap/support/lambda.hpp>

#include <boost/multi_array.hpp>

#include <boost/container/vector.hpp>
#include <boost/container/stable_vector.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>

#include <boost/circular_buffer.hpp>

#include <boost/heap/binomial_heap.hpp>
#include <boost/heap/priority_queue.hpp>

// Internal
#include "containers/graph.h"

namespace utl {
    // First class containers
    using boost::container::stable_vector;

    namespace recursive {
        using boost::container::vector;
    }

    using boost::bimap;
    using namespace boost::bimaps;

    using boost::multi_array;
    namespace multi_array_types{
        using namespace boost::multi_array_types;
    }
    using boost::extents;
    using boost::indices;
    using boost::detail::multi_array::sub_array;
    using boost::detail::multi_array::const_sub_array;
    using boost::detail::multi_array::array_iterator;
    using boost::detail::multi_array::const_multi_array_view;
    using boost::detail::multi_array::multi_array_view;
    using boost::multi_array_ref;
    using boost::const_multi_array_ref;
    using namespace boost::multi_index;

    // second class containers
    namespace heap {
        using namespace boost::heap;
    }
    using boost::heap::binomial_heap;

    using boost::circular_buffer;

}

#endif //WPP_CONTAINER_UTILS_H
