#ifndef UTILITIES_TYPETRAITS_H
#define UTILITIES_TYPETRAITS_H

#include <cstdlib>
#include <tuple>
#include <functional>
#include <type_traits>
#include "prettyprint.hpp"

namespace utl {

    template<class T>
    struct is_c_str
            : std::integral_constant<
                    bool,
                    std::is_same<char const *, typename std::decay<T>::type>::value ||
                    std::is_same<char *, typename std::decay<T>::type>::value ||
                    std::is_same<char[], typename std::decay<T>::type>::value
            > {
    };
    template<typename T>
    struct is_arithmetic_or_string_variable
            : std::integral_constant<bool, std::is_arithmetic<std::decay<T>>::value ||
                                           std::is_assignable<std::string, std::decay<T>>::value ||
                                           is_c_str<T>::value> {
    };
    template<typename T>
    struct is_arithmetic_or_string
            : std::integral_constant<bool,
                    is_arithmetic_or_string_variable<std::decay<T>>::value> {
    };
    template<typename T>
    struct is_arithmetic_or_string_reference
            : std::integral_constant<bool,
                    is_arithmetic_or_string<T>::value && std::is_reference<T>::value> {
    };
    template<typename T>
    struct is_arithmetic_or_string_const
            : std::integral_constant<bool, is_arithmetic_or_string<T>::value && std::is_const<T>::value> {
    };
    template<typename T>
    struct is_pure_char
            : std::integral_constant<bool,
                    std::is_same<T, char>::value || std::is_same<T, char16_t>::value ||
                    std::is_same<T, char32_t>::value || std::is_same<T, wchar_t>::value ||
                    std::is_same<T, signed char>::value> {
    };
    template<typename T>
    struct is_bool
            : std::integral_constant<bool, std::is_same<T, bool>::value> {
    };
    template<typename T>
    struct is_pure_int
            : std::integral_constant<bool,
                    std::is_integral<T>::value && !is_bool<T>::value && !is_pure_char<T>::value> {
    };

    template<typename T>
    class has_stream {
            typedef char one;
            typedef long two;

            template<typename C>
            static one test(typeof(&C::operator<<));

            template<typename C>
            static two test(...);

        public:
            enum { value = sizeof(test<T>(0)) == sizeof(char) };
    };


    #define DECLARE_HAS_TYPE_MEMBER(member_name) \
    template <typename, typename = void> \
    struct has_##member_name \
    { enum { value = false }; }; \
    template <typename T> \
    struct has_##member_name<T, typename std::enable_if<sizeof(typename T::member_name)||true>::type> \
    { enum { value = true }; };

    template<typename T>
    struct function_traits
            : public function_traits<decltype(&T::operator())> {
    };

    namespace xx_impl {
        template<typename C, typename R, typename... A>
        struct memfn_type {
            typedef typename std::conditional<
                    std::is_const<C>::value,
                    typename std::conditional<
                            std::is_volatile<C>::value,
                            R (C::*)(A...) const volatile,
                            R (C::*)(A...) const
                    >::type,
                    typename std::conditional<
                            std::is_volatile<C>::value,
                            R (C::*)(A...) volatile,
                            R (C::*)(A...)
                    >::type
            >::type type;
        };
    }

    template<typename ReturnType, typename... Args>
    struct function_traits<ReturnType(Args...)> {
        typedef ReturnType result_type;
        typedef ReturnType function_type(Args...);
        template<typename OwnerType>
        using member_function_type = typename xx_impl::memfn_type<
                typename std::remove_pointer<typename std::remove_reference<OwnerType>::type>::type,
                ReturnType, Args...
        >::type;
        enum { arity = sizeof...(Args) };
        template<size_t i>
        struct arg {
            typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        };
    };

    template<typename ReturnType, typename... Args>
    struct function_traits<ReturnType(*)(Args...)>
            : public function_traits<ReturnType(Args...)> {
    };

    template<typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...)>
            : public function_traits<ReturnType(Args...)> {
        typedef ClassType &owner_type;
    };

    template<typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) const>
            : public function_traits<ReturnType(Args...)> {
        typedef const ClassType &owner_type;
    };

    template<typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) volatile>
            : public function_traits<ReturnType(Args...)> {
        typedef volatile ClassType &owner_type;
    };

    template<typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType(ClassType::*)(Args...) const volatile>
            : public function_traits<ReturnType(Args...)> {
        typedef const volatile ClassType &owner_type;
    };

    template<typename FunctionType>
    struct function_traits<std::function<FunctionType>>
            : public function_traits<FunctionType> {
    };

    #if defined(_GLIBCXX_FUNCTIONAL)
    #define MEM_FN_SYMBOL_XX0SL7G4Z0J std::_Mem_fn
    #elif defined(_LIBCPP_FUNCTIONAL)
    #define MEM_FN_SYMBOL_XX0SL7G4Z0J std::__mem_fn
    #endif

    #ifdef MEM_FN_SYMBOL_XX0SL7G4Z0J

    template<typename R, typename C>
    struct function_traits<MEM_FN_SYMBOL_XX0SL7G4Z0J<R C::*>>
            : public function_traits<R(C *)> {
    };
    template<typename R, typename C, typename... A>
    struct function_traits<MEM_FN_SYMBOL_XX0SL7G4Z0J<R(C::*)(A...)>>
            : public function_traits<R(C *, A...)> {
    };
    template<typename R, typename C, typename... A>
    struct function_traits<MEM_FN_SYMBOL_XX0SL7G4Z0J<R(C::*)(A...) const>>
            : public function_traits<R(const C *, A...)> {
    };
    template<typename R, typename C, typename... A>
    struct function_traits<MEM_FN_SYMBOL_XX0SL7G4Z0J<R(C::*)(A...) volatile>>
            : public function_traits<R(volatile C *, A...)> {
    };
    template<typename R, typename C, typename... A>
    struct function_traits<MEM_FN_SYMBOL_XX0SL7G4Z0J<R(C::*)(A...) const volatile>>
            : public function_traits<R(const volatile C *, A...)> {
    };

    #undef MEM_FN_SYMBOL_XX0SL7G4Z0J
    #endif

    template<typename T>
    struct function_traits<T &>
            : public function_traits<T> {
    };
    template<typename T>
    struct function_traits<const T &>
            : public function_traits<T> {
    };
    template<typename T>
    struct function_traits<volatile T &>
            : public function_traits<T> {
    };
    template<typename T>
    struct function_traits<const volatile T &>
            : public function_traits<T> {
    };
    template<typename T>
    struct function_traits<T &&>
            : public function_traits<T> {
    };
    template<typename T>
    struct function_traits<const T &&>
            : public function_traits<T> {
    };
    template<typename T>
    struct function_traits<volatile T &&>
            : public function_traits<T> {
    };
    template<typename T>
    struct function_traits<const volatile T &&>
            : public function_traits<T> {
    };


    #define FORWARD_RES_8QR485JMSBT \
    typename std::conditional< \
        std::is_lvalue_reference<R>::value, \
        T&, \
        typename std::remove_reference<T>::type&& \
    >::type

    template<typename R, typename T>
    FORWARD_RES_8QR485JMSBT forward_like(T &&input) noexcept {
        return static_cast<FORWARD_RES_8QR485JMSBT>(input);
    }

    template<typename T>
    struct pointee {
        typedef typename std::remove_reference<decltype(*std::declval<T>())>::type type;
    };

    template<typename T>
    typename std::add_rvalue_reference<T>::type rt_val() noexcept {
        return std::move(*static_cast<T *>(nullptr));
    }

    template<class T>
    struct Void {
        typedef void type;
    };

    template<class T, class U = void>
    struct has_value_type {
        enum { value = 0 };
    };

    template<class T>
    struct has_value_type<T, typename Void<typename T::value_type>::type > {
        enum { value = 1 };
    };

    template<typename T>
    struct is_container : public pretty_print::is_container<T> {};

    template<class T, class U = void>
    struct has_container_value_type {
        enum { value = 0 };
    };

    template<class T>
    struct has_container_value_type<T, typename Void<typename T::value_type>::type > {
        enum { value = utl::is_container<typename T::value_type>::value };
    };

    template<typename T>
    struct is_container_of_container : std::integral_constant<bool, utl::is_container<T>::value && utl::has_container_value_type<T>::value> {};

    template<typename T>
    struct is_container_of_non_container : std::integral_constant<bool, utl::is_container<T>::value && !utl::is_container_of_container<T>::value> {};

    template<class T, class U = void>
    struct has_scalar_value_type {
        enum { value = 0 };
    };

    template<class T>
    struct has_scalar_value_type<T, typename Void<typename T::value_type>::type > {
        enum { value = std::is_scalar<typename T::value_type>::value };
    };

    template<typename T>
    struct is_container_of_scalar : std::integral_constant<bool, utl::is_container<T>::value && utl::has_scalar_value_type<T>::value> {};

    template<typename T>
    struct is_container_of_container_of_scalar; // recursive forward declaration

    template<class T, class U = void>
    struct has_scalar_container_value_type {
        enum { value = 0 };
    };

    template<class T>
    struct has_scalar_container_value_type<T, typename Void<typename T::value_type>::type > {
        enum { value = utl::is_container_of_scalar<typename T::value_type>::value || utl::is_container_of_container_of_scalar<typename T::value_type>::value };
    };

    template<typename T>
    struct is_container_of_container_of_scalar : std::integral_constant<bool, utl::is_container<T>::value && utl::has_scalar_container_value_type<T>::value> {};

}

#endif

