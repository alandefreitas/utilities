//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_ALGORITHM_UTILS_H
#define WPP_ALGORITHM_UTILS_H

// External
// Range algorithms
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/for_each.hpp>
#include <boost/range/algorithm_ext/overwrite.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm_ext/push_front.hpp>
#include <boost/range/algorithm_ext/insert.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/range/numeric.hpp>

// Filter ranges

#include <boost/range/adaptors.hpp>

// Create ranges
#include <boost/range/irange.hpp>
#include <boost/range/istream_range.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/combine.hpp>

// Helpers
#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/cast.hpp>

// Algorithms that don't exists in the STL
#include <boost/algorithm/cxx11/iota.hpp>
#include <boost/algorithm/cxx11/one_of.hpp>
#include <boost/algorithm/searching/boyer_moore_horspool.hpp>
#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

// Internal
#include "join_range.h"
// Algorithms that exist in the STL but don't have ranges
#include "range_cxx11_algorithms.h"

namespace utl {
    using namespace boost::range;

    namespace view {
        using namespace boost::adaptors;
        using boost::integer_range;
        using boost::irange;
        using boost::iterator_range;
        using boost::istream_range;
        using boost::iterator_range;
        using boost::sub_range;
        using boost::combine;
    }

    using boost::accumulate;
    using boost::inner_product;
    using boost::partial_sum;
    using boost::adjacent_difference;

    using boost::algorithm::clamp;
    using boost::algorithm::hex;
    using boost::algorithm::unhex;

    using boost::algorithm::iota;
    using boost::algorithm::iota_n;

    using boost::algorithm::one_of;
    using boost::algorithm::one_of_equal;

    using boost::algorithm::boyer_moore_horspool;
    using boost::algorithm::boyer_moore;
    using boost::algorithm::knuth_morris_pratt;

    using boost::polymorphic_downcast;
    using boost::polymorphic_cast;

}

#endif //WPP_ALGORITHM_UTILS_H
