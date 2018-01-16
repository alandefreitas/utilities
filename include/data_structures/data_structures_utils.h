//
// Created by Alan de Freitas on 04/01/18.
//

#ifndef UTILITIES_DATA_STRUCTURES_UTILS_H
#define UTILITIES_DATA_STRUCTURES_UTILS_H

#include <json.hpp>
#include <boost/any.hpp>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/property_tree/ptree.hpp>

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

#include <boost/variant.hpp>

#include <boost/fusion/tuple.hpp>
#include <boost/fusion/view.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/int.hpp>

namespace utl {

    using json = nlohmann::json;

    template<class T>
    using optional = boost::optional<T>;

    template<class T>
    inline optional<T> make_optional ( T v )
    {
        return ::boost::make_optional(v);
    }

    template<class T>
    inline optional<T> make_optional ( bool cond, T v )
    {
        return ::boost::make_optional(cond,v);
    }

    template <typename R = ::boost::detail::static_visitor_default_return>
    using static_visitor = boost::static_visitor<R>;

    using boost::any;
    using boost::bad_any_cast;

    template<typename ValueType>
    ValueType * any_cast(any * operand) noexcept
    {
        return ::boost::any_cast<ValueType>(operand);
    }

    template<typename ValueType>
    inline const ValueType * any_cast(const any * operand) noexcept
    {
        return ::boost::any_cast<ValueType>(operand);
    }

    template<typename ValueType, typename AnyType>
    ValueType any_cast(AnyType operand)
    {
        return ::boost::any_cast<ValueType>(operand);
    }

    namespace property_tree{
        using namespace boost::property_tree;
    }

    using boost::property_tree::ptree;

    template <typename... Types>
    using variant = boost::variant<Types...>;

    namespace getter {
        using boost::get;
    }

    namespace fusion = boost::fusion;
    namespace mpl = boost::mpl;

    using namespace boost::logic;
}

#endif //UTILITIES_DATA_STRUCTURES_UTILS_H
