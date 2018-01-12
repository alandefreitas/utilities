//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef PHP_CONTAINER_UTILS_H
#define PHP_CONTAINER_UTILS_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#include <numeric>
#include <random>
#include <cmath>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>
#include <set>

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>

namespace utl {

    // using ...

    // array_shift() shifts the first value of the array off and returns it, shortening the array by one element
    // take mean of the elements
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T array_shift(C<T> &c) {
        T t = c[0];
        c.erase(c.begin());
        return t;
    }

    template<class C>
    typename C::value_type array_shift(C &c) {
        typename C::value_type t = c[0];
        c.erase(c.begin());
        return t;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    T array_unshift(C<T> &c, T t) {
        c.insert(c.begin(),t);
        return t;
    }

    inline int microtime_milliseconds() {
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        return ms.count();
    }

    inline double microtime() {
        using namespace std::chrono;
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        double f = ms.count();
        f /= 1000;
        return f;
    }

    inline double round(double v, int precision){
        const double exp = std::pow(10,precision);
        return std::round(v*exp)/exp;
    }

    template<typename T>
    void func_get_args(std::vector<T> &v, T t) // recursive variadic function
    {
        v.push_back(t);
    }

    template<typename T, typename... TS>
    void func_get_args(std::vector<T> &v, T t, TS... args) // recursive variadic function
    {
        v.push_back(t);
        func_get_args(v, args...);
    }

    // Returns an array comprising a function's argument list
    template<typename T>
    std::vector<T> func_get_args(T t) {
        return std::vector<T>({t});
    }

    template<typename T, typename... TS>
    std::vector<T> func_get_args(TS... args) // recursive variadic function
    {
        std::vector<T> v;
        func_get_args(v, args...);
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    bool in_array(const T t, const C<T> c) {
        return c.find(c.begin(),c.end(),t) != c.end();
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> array_slice(C<T> array, size_t offset, size_t length) {
        if (array.begin()+offset < array.end()){
            if (array.begin()+offset+length < array.end()){
                return C<T>(array.begin()+offset, array.begin()+offset+length);
            } else {
                return C<T>(array.begin()+offset, array.end());
            }
        } else {
            return C<T>();
        }

    }

    template<class ResultContainer>
    ResultContainer array_slice(ResultContainer results, size_t offset, size_t length) {
        using row = decltype(results.front());
        if (results.begin()+offset < results.end()){
            if (results.begin()+offset+length < results.end()){
                return ResultContainer(results.begin()+offset, results.begin()+offset+length);
            } else {
                return ResultContainer(results.begin()+offset, results.end());
            }
        } else {
            return ResultContainer();
        }

    }


    template<typename FUNC, typename ARRAY>
    ARRAY array_map(FUNC f, ARRAY _values){
        for (auto &&value :_values) {
            value = f(value);
        }
    };
    
    inline std::vector<int> range_vector(int start, int end, int step = 1){
        if (start > end){
            return range_vector(end,start,step);
        }
        std::vector<int> v;
        v.reserve((end-start)/step);
        for (int i = start; i <= end; i+=step) {
            v.push_back(i);
        }
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> array_merge(C<T> c1, C<T> &c2) {
        c1.insert(c1.end(),c2.begin(),c2.end());
        return c1;
    }


}

#endif //PHP_CONTAINER_UTILS_H
