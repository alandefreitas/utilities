//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_MEMORY_UTILS_H
#define WPP_MEMORY_UTILS_H

// External
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/pool/pool_alloc.hpp>
#define BOOST_POOL_NO_MT
#include <boost/pool/pool_alloc.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/set_factory.hpp>
#include <boost/flyweight/no_locking.hpp>
#include <boost/flyweight/no_tracking.hpp>

// Internal
namespace utl {
    namespace flyweights = boost::flyweights;
    using boost::flyweight;
    using boost::singleton_pool;
}

#endif //WPP_MEMORY_UTILS_H
