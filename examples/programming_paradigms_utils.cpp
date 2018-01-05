#include <cstdio>
#include <typeinfo>
#include <string>
#include <type_traits>
#include <functional>
#include <iostream>
#include <map>
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include <cxxabi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include "utils.h"

using namespace std;
using namespace utl;

void cooperative(coroutine<void>::push_type &sink);
void cooperative2(coroutine<int>::push_type &sink, int i);
void cooperative3(coroutine<tuple<int, string>>::pull_type &source);
void cooperative4(coroutine<void>::push_type &sink);

template <typename T>
typename enable_if<is_same<T, int>::value, T>::type create()  { return 1; }

template <typename T>
typename enable_if<is_same<T, string>::value, T>::type create() { return "String"; }

template <typename T>
void print(typename enable_if<is_integral<T>::value, T>::type i) { cout << "Integral: " << i << '\n'; }

template <typename T>
void print(typename enable_if<is_floating_point<T>::value, T>::type f) { cout << "Floating point: " << f << '\n'; }

template<typename A, typename B>
void check() {
    printf("[%s] %s\n", is_same<A,B>::value ? "pass" : "fail", A::data());
}

using test1 = irqus::typestring<'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ',', ' ', 'h', 'o', 'w', ' ', 'i', 's', ' ', 'i', 't', ' ', 'g', 'o', 'i', 'n', 'g', '?'>;

using test2 = irqus::typestring<'u', 'p', 'p', 'e', 'r', 'c', 'a', 's', 'e', ':', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' >;

using test3 = irqus::typestring< 'l', 'o', 'w', 'e', 'r', 'c', 'a', 's', 'e', ':', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' >;

using test4 = irqus::typestring< 'f', 'l','o', 'a', 't', 'i', 'n', 'g', ' ', ':', ' ', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', 'e', '-', '1', '2', '3', '4'>;

using test5 = irqus::typestring< 's', 'y', 'm', 'b', 'o', 'l', 's', ' ', ' ', ':', ' ', '~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '=','-', '[', ']', '\\', '{', '}', '|', ':', ';', '\'', ',', '.', '?', '/'>;

bool is_odd(int i) { return i % 2 == 1; }

struct is_odd_impl
{
    typedef bool result_type;

    template <typename T>
    bool operator()(T t) const { return t % 2 == 1; }
};

phoenix::function<is_odd_impl> is_odd_obj;

bool is_odd_function(int i) { return i % 2 == 1; }

BOOST_PHOENIX_ADAPT_FUNCTION(bool, is_odd_phoenix, is_odd_function, 1)

struct print {
    template<typename T>
    void operator()(const T &t) const {
        cout << boolalpha << t << '\n';
    }
};

int main()
{
    cout << bold << on_yellow << "Demangling" << reset << endl;
    cout << bold << underline << "Printing and comparing types and values" << reset << endl;
    {
        cout << "demangle<int*>(): " << demangle<int*>() << endl;
        check_type_equal<int, int *>();
        check_type_equal<int, int&>();
        check_type_equal<int, int>();
        check_equal(2,4.5);
        check_equal(2,4);
        check_equal(2,2);
    }

    cout << bold << on_yellow << "Function typetraits" << reset << endl;

    cout << bold << underline << "Function Traits" << reset << endl;
    {
        typedef utl::function_traits<int(long, double *, const char &&, nullptr_t)> FT;
        cout << "function_traits<int(long, double *, const char &&, nullptr_t)> FT" << endl;
        cout << "FT::result_type == int: " << (typeid(FT::result_type) == typeid(int)) << endl;
        cout << "FT::arity: " << (FT::arity) << endl;
        cout << "FT::arg<0>::type == long: " << (typeid(FT::arg<0>::type) == typeid(long)) << endl;
        cout << "FT::arg<1>::type == double * : " << (typeid(FT::arg<1>::type) == typeid(double * )) << endl;
        cout << "FT::arg<2>::type == const char&&): " << (typeid(FT::arg<2>::type) == typeid(const char&&)) << endl,
        cout << "FT::arg<3>::type == nullptr_t: " << (typeid(FT::arg<3>::type) == typeid(nullptr_t)) << endl;
    }

    cout << bold << underline << "Function Pointer - Traits" << reset << endl;
    {
        int f(pair<int, void*>, volatile double*, long(*)(size_t));
        typedef utl::function_traits<decltype(&f)> FT;
        check_type_equal<FT::result_type, int>();
        check_equal(FT::arity, 3);
        check_type_equal<FT::arg<0>::type, pair<int, void*>>();
        check_type_equal<FT::arg<1>::type, volatile double*>();
        check_type_equal<FT::arg<2>::type, long(*)(size_t)>();
    }

    cout << bold << underline << "function_reference_test_case" << reset << endl;
    {
        typedef utl::function_traits<void(&)()> FT;

        check_type_equal<FT::result_type, void>();
        check_equal(FT::arity, 0);
    }

    cout << bold << underline << "function rvalue reference test_case" << reset << endl;
    {
        typedef utl::function_traits<int(*(&&)(const long&&))[]> FT;

        check_type_equal<FT::result_type, int(*)[]>();
        check_equal(FT::arity, 1);
        check_type_equal<FT::arg<0>::type, const long&&>();
    }

    cout << bold << underline << "member pointer test case" << reset << endl;
    {
        struct S
        {
            short p(const char*) noexcept;
            unsigned int q(pair<int, int>, int) const volatile throw();
            bool operator==(const S&) const;
            virtual void r() volatile {}
            virtual ~S() {}
        };

        typedef utl::function_traits<decltype(&S::p)> FTp;
        check_type_equal<FTp::owner_type, S&>();
        check_type_equal<FTp::result_type, short>();
        check_equal(FTp::arity, 1);
        check_type_equal<FTp::arg<0>::type, const char*>();

        typedef utl::function_traits<decltype(&S::q)> FTq;
        check_type_equal<FTq::owner_type, const volatile S&>();
        check_type_equal<FTq::result_type, unsigned int>();
        check_equal(FTq::arity, 2);
        check_type_equal<FTq::arg<0>::type, pair<int, int>>();
        check_type_equal<FTq::arg<1>::type, int>();

        typedef utl::function_traits<decltype(&S::operator==)> FTe;
        check_type_equal<FTe::owner_type, const S&>();
        check_type_equal<FTe::result_type, bool>();
        check_equal(FTe::arity, 1);
        check_type_equal<FTe::arg<0>::type, const S&>();

        typedef utl::function_traits<decltype(&S::r)> FTr;
        check_type_equal<FTr::owner_type, volatile S&>();
        check_type_equal<FTr::result_type, void>();
        check_equal(FTr::arity, 0);

        const auto& sr = &S::r;
        typedef utl::function_traits<decltype(sr)> FTr2;
        check_type_equal<FTr2::owner_type, volatile S&>();
        check_type_equal<FTr2::result_type, void>();
        check_equal(FTr2::arity, 0);
    }

    cout << bold << underline << "Function object test case" << reset << endl;
    {
        typedef utl::function_traits<function<long(int*, char** const*)>> FT;

        check_type_equal<FT::result_type, long>();
        check_equal(FT::arity, 2);
        check_type_equal<FT::arg<0>::type, int*>();
        check_type_equal<FT::arg<1>::type, char** const*>();
    }

    cout << bold << underline << "Other function object test case" << reset << endl;
    {
        typedef utl::function_traits<plus<int>> FTplus;
        check_type_equal<FTplus::result_type, int>();
        check_equal(FTplus::arity, 2);
        check_type_equal<FTplus::arg<0>::type, const int&>();
        check_type_equal<FTplus::arg<1>::type, const int&>();

        typedef utl::function_traits<equal_to<string>> FTequal;
        check_type_equal<FTequal::result_type, bool>();
        check_equal(FTequal::arity, 2);
        check_type_equal<FTequal::arg<0>::type, const string&>();
        check_type_equal<FTequal::arg<1>::type, const string&>();

        typedef utl::function_traits<logical_not<void*>> FTnot;
        check_type_equal<FTnot::result_type, bool>();
        check_equal(FTnot::arity, 1);
        check_type_equal<FTnot::arg<0>::type, void* const&>();

        typedef utl::function_traits<decltype(not2(plus<double>()))> FTnotplus;
        check_type_equal<FTnotplus::result_type, bool>();
        check_equal(FTnotplus::arity, 2);
        check_type_equal<FTnotplus::arg<0>::type, const double&>();
        check_type_equal<FTnotplus::arg<1>::type, const double&>();
    }

    cout << bold << underline << "Lambda test case" << reset << endl;
    {
        double x = 4;
        auto lambda = [=](int y) { return x + y; };

        typedef utl::function_traits<decltype(lambda)> FT;
        check_type_equal<FT::result_type, double>();
        check_equal(FT::arity, 1);
        check_type_equal<FT::arg<0>::type, int>();

        auto lambda2 = [&](float z) mutable -> void* { x = z; return nullptr; };
        typedef utl::function_traits<decltype(lambda2)> FT2;
        check_type_equal<FT2::result_type, void*>();
        check_equal(FT2::arity, 1);
        check_type_equal<FT2::arg<0>::type, float>();
    }

    cout << bold << underline << "Mem fn test case" << reset << endl;
    {
        struct K
        {
            int p;
            double q(float r) const { return 0.0; }
        };

        auto pp = mem_fn(&K::p);
        auto qq = mem_fn(&K::q);

        typedef utl::function_traits<decltype(pp)> FTp;
        typedef utl::function_traits<decltype(qq)> FTq;

        check_type_equal<FTp::result_type, int>();
        check_equal(FTp::arity, 1);
        check_type_equal<FTp::arg<0>::type, K*>();
        check_type_equal<FTq::result_type, double>();
        check_equal(FTq::arity, 2);
        check_type_equal<FTq::arg<0>::type, const K*>();
        check_type_equal<FTq::arg<1>::type, float>();
    }

    cout << bold << underline << "Member function type" << reset << endl;
    {
        struct S;

        typedef utl::function_traits<float(double)> FType;
        check_type_equal<FType::member_function_type<S>, float(S::*)(double)>();
        check_type_equal<FType::member_function_type<const S&>, float(S::*)(double) const>();
        check_type_equal<FType::member_function_type<volatile S>, float(S::*)(double) volatile>();
        check_type_equal<FType::member_function_type<const volatile S*>, float(S::*)(double) const volatile>();
    }

    cout << bold << on_yellow << "Generic Typetraits" << reset << endl;

    cout << bold << underline << "Copy cv test case" << reset << endl;
    {
        check_type_equal<utl::copy_cv<const int, double>::type, const double>();
        check_type_equal<utl::copy_cv<int, const double>::type, double>();
        check_type_equal<utl::copy_cv<int* volatile, long long>::type, volatile long long>();
        check_type_equal<utl::copy_cv<const char*, int>::type, int>();
    }

    cout << bold << underline << "Pointee test case" << reset << endl;
    {
        check_type_equal<utl::pointee<int*>::type, int>();
        check_type_equal<utl::pointee<int**>::type, int*>();
        check_type_equal<utl::pointee<const int*>::type, const int>();
        check_type_equal<utl::pointee<string::const_iterator>::type, const char>();
        typedef map<short, char> Map;
        check_type_equal<utl::pointee<Map::reverse_iterator>::type, Map::value_type>();
    }

    cout << bold << underline << "Determining type categories" << reset
         << endl;
    {
        cout.setf(ios::boolalpha);
        cout << "is_integral<int>::value: " << is_integral<int>::value << '\n';
        cout << "is_floating_point<int>::value: " << is_floating_point<int>::value << '\n';
        cout << "is_arithmetic<int>::value: " << is_arithmetic<int>::value << '\n';
        cout << "is_reference<int>::value: " << is_reference<int>::value << '\n';
    }

    cout << bold << underline << "true_type and false_type" << reset
         << endl;
    {
        cout.setf(ios::boolalpha);
        cout << "is_same<is_integral<int>::type, true_type>::value: " << is_same<is_integral<int>::type, true_type>::value << '\n';
        cout << "is_same<is_floating_point<int>::type, false_type>:: " << is_same<is_floating_point<int>::type, false_type>::value <<
             '\n';
        cout << "is_same<is_arithmetic<int>::type, true_type>::value: " << is_same<is_arithmetic<int>::type, true_type>::value << '\n';
        cout << "is_same<is_reference<int>::type, false_type>::value: " << is_same<is_reference<int>::type, false_type>::value << '\n';
    }

    cout << bold << underline << "Checking type properties with Boost.TypeTraits"
         << reset << endl;
    {
        cout.setf(ios::boolalpha);
        cout << "has_plus<int>::value: " << has_plus<int>::value << '\n';
        cout << "has_pre_increment<int>::value: " << has_pre_increment<int>::value << '\n';
        cout << "has_trivial_copy<int>::value: " << has_trivial_copy<int>::value << '\n';
        cout << "has_virtual_destructor<int>::value: " << has_virtual_destructor<int>::value << '\n';
    }

    cout << bold << underline << "Changing type properties with Boost.TypeTraits"
         << reset << endl;
    {
        cout.setf(ios::boolalpha);
        cout << "is_const<add_const<int>::type>::value: " << is_const<add_const<int>::type>::value << '\n';
        cout << "is_same<remove_pointer<int *>::type, int>::value: " << is_same<remove_pointer<int *>::type, int>::value << '\n';
        cout << "is_same<make_unsigned<int>::type, unsigned int>:: " << is_same<make_unsigned<int>::type, unsigned int>::value <<
             '\n';
        cout << "is_same<add_rvalue_reference<int>::type, int &&>:: " << is_same<add_rvalue_reference<int>::type, int &&>::value <<
             '\n';
    }

    cout << bold << underline << "Overloading functions with enable_if on their return value" << reset << endl;
    {
        cout << create<string>() << '\n';
    }

    cout << bold << underline << "Specializing functions for a group of types with enable_if" << reset << endl;
    {
        print<short>(1);
        print<long>(2);
        print<double>(3.14);
    }


    cout << bold << on_yellow << "Coroutines" << reset << endl;

    cout << bold << underline << "Using coroutines" << reset << endl;
    {
        coroutine<void>::pull_type source{cooperative};
        cout << ", ";
        source();
        cout << "!\n";
    }

    cout << bold << underline << "Returning a value from a coroutine" << reset << endl;
    {
        using std::placeholders::_1;
        coroutine<int>::pull_type source{bind(cooperative2, _1, 0)};
        cout << source.get() << '\n';
        source();
        cout << source.get() << '\n';
        source();
    }

    cout << bold << underline << "Passing two values to a coroutine" << reset << endl;
    {
        coroutine<tuple<int, string>>::push_type sink{cooperative3};
        sink(make_tuple(0, "aaa"));
        sink(make_tuple(1, "bbb"));
        cout << "end\n";
    }

    cout << bold << underline << "Coroutines and exceptions" << reset << endl;
    {
        coroutine<void>::pull_type source{cooperative4};
        try
        {
            source();
        }
        catch (const runtime_error &e)
        {
            cerr << e.what() << '\n';
        }
    }



    cout << bold << on_yellow << "Type String" << reset << endl;
    cout << bold << underline << "Comparing" << reset << endl;
    {
        check<typestring_is("Hello world, how is it going?"),test1 > ();
        check<typestring_is("uppercase: ABCDEFGHIJKLMNOPQRSTUVWXYZ"),test2 > ();
        check<typestring_is("lowercase: abcdefghijklmnopqrstuvwxyz"),test3 > ();
        check<typestring_is("floating : 123456789.123456789+e-1234"),test4 > ();
        check<typestring_is("symbols  : ~`!@#$%^&*()_+=-[]\\{}|:;',.?/"),test5 > ();
        check<typestring_is(""),irqus::typestring<'\0'>>
        (); // null!
        check<irqus::tycat<typestring_is("ABC")
        , typestring_is("DEF")
        , typestring_is("1234")>
        , typestring_is("ABCDEF1234") >();

        typedef typestring_is("Hello!") test; /* irqus::typestring<'H','e','l','l','o','!'> */
        cout << typeid(test).name() << endl;
        cout << typeid(typestring_is("Hello!")).name() << endl;
    }

    cout << bold << underline << "Demangling" << reset << endl;
    {
        cout << typeid(typestring_is("www.site.com/home/option.php?r=2")).name() << endl;
        string demangledName = utl::demangle<typestring_is("www.site.com/home/option.php?r=2")>();
        cout << "www.site.com/home/option.php?r=2" << endl;
        cout << demangledName << endl;

        erase_all(demangledName, "(char)");
        erase_all(demangledName, "<");
        erase_all(demangledName, ">");
        erase_all(demangledName, "typestring");
        erase_all(demangledName, "irqus");
        erase_all(demangledName, "::");
        erase_all(demangledName, ",");
        cout << demangledName << '\n';

        typedef tokenizer<char_separator<char>> tokenizer;
        string s = demangledName;
        char_separator<char> sep{" "};
        tokenizer tok{s, sep};
        string url_demangled;
        for (const auto &t : tok) {
            cout << t << ',';
            url_demangled.push_back(char(stoi(string(t))));
        }
        cout << endl;

        cout << url_demangled << endl;
    }

    cout << bold << on_yellow << "Phoenix Functional" << reset << endl;
    cout << bold << underline << "Predicates as global function, lambda function, and Phoenix function"
              << reset << endl;
    {
        vector<int> v{1, 2, 3, 4, 5};

        cout << count_if(v.begin(), v.end(), is_odd) << '\n';

        auto lambda = [](int i){ return i % 2 == 1; };
        cout << count_if(v.begin(), v.end(), lambda) << '\n';

        using namespace phoenix::placeholders;
        auto phoenix = arg1 % 2 == 1;
        cout << count_if(v.begin(), v.end(), phoenix) << '\n';
    }

    cout << bold << underline << "Phoenix function versus lambda function" << reset << endl;
    {
        vector<int> v{1, 2, 3, 4, 5};

        auto lambda = [](int i){ return i % 2 == 1; };
        cout << count_if(v.begin(), v.end(), lambda) << '\n';

        vector<long> v2;
        v2.insert(v2.begin(), v.begin(), v.end());

        using namespace phoenix::placeholders;
        auto phoenix = arg1 % 2 == 1;
        cout << count_if(v.begin(), v.end(), phoenix) << '\n';
        cout << count_if(v2.begin(), v2.end(), phoenix) << '\n';
    }

    cout << bold << underline << "Phoenix functions as deferred C++ code" << reset << endl;
    {
        vector<int> v{1, 2, 3, 4, 5};

        using namespace phoenix::placeholders;
        auto phoenix = arg1 > 2 && arg1 % 2 == 1;
        cout << count_if(v.begin(), v.end(), phoenix) << '\n';
    }

    cout << bold << underline << "Explicit Phoenix types" << reset << endl;
    {
        vector<int> v{1, 2, 3, 4, 5};

        using namespace phoenix;
        using namespace phoenix::placeholders;
        auto phoenix = arg1 > val(2) && arg1 % val(2) == val(1);
        cout << count_if(v.begin(), v.end(), phoenix) << '\n';
    }

    cout << bold << underline << "phoenix::placeholders::arg1 and phoenix::val()" << reset << endl;
    {
        using namespace phoenix::placeholders;
        cout << arg1(1, 2, 3, 4, 5) << '\n';

        auto v = phoenix::val(2);
        cout << v() << '\n';
    }

    cout << bold << underline << "Creating your own Phoenix functions" << reset << endl;
    {
        vector<int> v{1, 2, 3, 4, 5};

        using namespace phoenix::placeholders;
        cout << count_if(v.begin(), v.end(), is_odd_obj(arg1)) << '\n';
    }

    cout << bold << underline << "Transforming free-standing functions into Phoenix functions" << reset << endl;
    {
        vector<int> v{1, 2, 3, 4, 5};

        using namespace phoenix::placeholders;
        cout << count_if(v.begin(), v.end(), is_odd_phoenix(arg1)) << '\n';
    }

    cout << bold << underline << "Arbitrarily complex Phoenix functions" << reset << endl;
    {
        vector<int> v{1, 2, 3, 4, 5};

        using namespace phoenix;
        using namespace phoenix::placeholders;
        int count = 0;
        for_each(v.begin(), v.end(), if_(arg1 > 2 && arg1 % 2 == 1)
        [
                ++phoenix::ref(count)
        ]);
        cout << count << '\n';
    }

    return 0;
}


void cooperative(coroutine<void>::push_type &sink)
{
    cout << "Hello";
    sink();
    cout << "world";
}

void cooperative2(coroutine<int>::push_type &sink, int i)
{
    int j = i;
    sink(++j);
    sink(++j);
    cout << "end\n";
}

void cooperative3(coroutine<tuple<int, string>>::pull_type &source)
{
    auto args = source.get();
    cout << get<0>(args) << " " << get<1>(args) << '\n';
    source();
    args = source.get();
    cout << get<0>(args) << " " << get<1>(args) << '\n';
}

void cooperative4(coroutine<void>::push_type &sink)
{
    sink();
    throw runtime_error("error");
}

