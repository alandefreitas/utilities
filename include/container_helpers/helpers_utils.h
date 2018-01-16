//
// Created by Alan de Freitas on 03/01/18.
//

#ifndef UTILITIES_HELPERS_UTILS_H
#define UTILITIES_HELPERS_UTILS_H

// EXTERNAL
#include <boost/operators.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/scoped_ptr.hpp>
#include <boost/serialization/export.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/program_options.hpp>

// INTERNAL
// plus, minus, etc for containers with numeric/scalar values
#include "container_overloads.h"
// functions with same format as matlab
#include "matlab_utils.h"
// (numeric) functions with same format as php
#include "php_utils.h"
// functions with same format as laravel
#include "laravel_utils.h"

namespace utl {
    using namespace boost::archive;
    using boost::scoped_ptr;
    using namespace boost::uuids;
    using namespace boost::program_options;

    namespace serialization = boost::serialization;
    using boost::lexical_cast;

    // operator traits
    using boost::less_than_comparable;
    using boost::equality_comparable;
    using boost::multipliable;
    using boost::addable;
    using boost::subtractable;
    using boost::dividable;
    using boost::modable;
    using boost::xorable;
    using boost::andable;
    using boost::orable;

    using boost::incrementable;
    using boost::decrementable;

    using boost::dereferenceable;
    using boost::indexable;

    using boost::left_shiftable;
    using boost::right_shiftable;
    using boost::equivalent;
    using boost::partially_ordered;

    using boost::totally_ordered;
    using boost::additive;
    using boost::multiplicative;
    using boost::integer_multiplicative;
    using boost::arithmetic;
    using boost::integer_arithmetic;
    using boost::bitwise;
    using boost::unit_steppable;
    using boost::shiftable;
    using boost::ring_operators;
    using boost::ordered_ring_operators;
    using boost::field_operators;
    using boost::ordered_field_operators;
    using boost::euclidian_ring_operators;
    using boost::ordered_euclidian_ring_operators;
    using boost::euclidean_ring_operators;
    using boost::ordered_euclidean_ring_operators;
    using boost::input_iteratable;
    using boost::output_iteratable;
    using boost::forward_iteratable;
    using boost::bidirectional_iteratable;
    using boost::random_access_iteratable;

}

#endif //UTILITIES_HELPERS_UTILS_H
