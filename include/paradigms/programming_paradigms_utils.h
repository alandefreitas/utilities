//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_PROGRAMMING_PARADIGMS_UTILS_H
#define WPP_PROGRAMMING_PARADIGMS_UTILS_H

// External
#include <boost/coroutine2/all.hpp>
#include "typestring.hh"
#include <boost/phoenix/phoenix.hpp>
#include <boost/type_traits.hpp>

// Internal
#include "traits.hpp"
#include "demangle.h"

namespace utl {
    // test type category
    using boost::is_base_and_derived;
    using boost::is_complex;
    using boost::is_final;
    using boost::is_float;
    using boost::is_lvalue_reference;
    using boost::is_stateless;
    using boost::is_virtual_base_of;
    // modify type
    using boost::add_reference;
    using boost::alignment_of;
    using boost::copy_cv;
    using boost::declval;
    using boost::floating_point_promotion;
    using boost::make_void;
    using boost::remove_bounds;
    using boost::type_identity;
    using boost::type_with_alignment;
    // test type members
    using boost::has_bit_and;
    using boost::has_bit_and_assign;
    using boost::has_bit_or;
    using boost::has_bit_or_assign;
    using boost::has_bit_xor;
    using boost::has_bit_xor_assign;
    using boost::has_complement;
    using boost::has_dereference;
    using boost::has_divides;
    using boost::has_divides_assign;
    using boost::has_equal_to;
    using boost::has_greater;
    using boost::has_greater_equal;
    using boost::has_left_shift;
    using boost::has_left_shift_assign;
    using boost::has_less;
    using boost::has_less_equal;
    using boost::has_logical_and;
    using boost::has_logical_not;
    using boost::has_logical_or;
    using boost::has_minus;
    using boost::has_minus_assign;
    using boost::has_modulus;
    using boost::has_modulus_assign;
    using boost::has_multiplies;
    using boost::has_multiplies_assign;
    using boost::has_negate;
    #if !defined(__BORLANDC__) && !defined(__CUDACC__)
    using boost::has_new_operator;
    #endif
    using boost::has_not_equal_to;
    using boost::has_nothrow_assign;
    using boost::has_nothrow_constructor;
    using boost::has_nothrow_copy;
    using boost::has_nothrow_destructor;
    using boost::has_plus;
    using boost::has_plus_assign;
    using boost::has_post_decrement;
    using boost::has_post_increment;
    using boost::has_pre_decrement;
    using boost::has_pre_increment;
    using boost::has_right_shift;
    using boost::has_right_shift_assign;
    using boost::has_trivial_assign;
    using boost::has_trivial_constructor;
    using boost::has_trivial_copy;
    using boost::has_trivial_destructor;
    using boost::has_trivial_move_assign;
    using boost::has_trivial_move_constructor;
    using boost::has_unary_minus;
    using boost::has_unary_plus;

    using namespace boost::coroutines2;
    namespace phoenix = boost::phoenix;
}

#endif //WPP_PROGRAMMING_PARADIGMS_UTILS_H
