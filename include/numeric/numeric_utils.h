//
// Created by Alan de Freitas on 04/01/18.
//

#ifndef UTILITIES_NUMERIC_UTILS_H
#define UTILITIES_NUMERIC_UTILS_H

// external
#include <cstdint>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/geometries/adapted/c_array.hpp>

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)

#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>

#include <boost/geometry/geometries/ring.hpp>
#include <boost/geometry/geometries/linestring.hpp>

// #include <hdf5_hl.h>

// internal
#include "random_shortcuts.h"
#include "statistics.h"

namespace utl {
    using namespace boost::numeric;
    namespace geometry {
        using namespace boost::geometry;
    }
    using boost::numeric_cast;
    using namespace boost::numeric;
}

#endif //UTILITIES_NUMERIC_UTILS_H
