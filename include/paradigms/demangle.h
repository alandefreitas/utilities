#ifndef UTILITIES_DEMANGLE_H
#define UTILITIES_DEMANGLE_H

#if defined( __has_include ) && (!defined( BOOST_GCC ) || (__GNUC__ + 0) >= 5)
# if __has_include(<cxxabi.h>)
#  define SYSTEM_HAS_CXXABI_H
# endif
#elif defined( __GLIBCXX__ ) || defined( __GLIBCPP__ )
# define SYSTEM_HAS_CXXABI_H
#endif

#if defined( SYSTEM_HAS_CXXABI_H )
# include <cxxabi.h>
# if defined( __GABIXX_CXXABI_H__ )
#  undef SYSTEM_HAS_CXXABI_H
# else
#  include <cstdlib>
#  include <cstddef>
# endif
#endif

namespace utl {
    template<typename T>
    std::string demangle() {
        const char *t_name = typeid(T).name();
        #ifdef SYSTEM_HAS_CXXABI_H
        int status;
        t_name = abi::__cxa_demangle(t_name, NULL, NULL, &status);
        #endif
        return t_name;
    }

    template <typename T, typename T2>
    void check_equal(T a, T2 b){
        if (a == b){
            std::cout << a << " == " << b << std::endl;
        } else {
            std::cout << a << " != " << b << std::endl;
        }
    }

    template <typename T1, typename T2>
    void check_type_equal(){
        if (typeid(T1) == typeid(T2)){
            std::cout << demangle<T1>() << " == " << demangle<T2>() << std::endl;
        } else {
            std::cout << demangle<T1>() << " != " << demangle<T2>() << std::endl;
        }
    }

}

#endif //UTILITIES_DEMANGLE_H
