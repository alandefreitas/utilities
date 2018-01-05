//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef MATLAB_METHOD_CONTAINER_UTILS_H
#define MATLAB_METHOD_CONTAINER_UTILS_H

#include <stdio.h>

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

namespace utl {


    //////////////////////////////////////////////
    //          CONTAINER METHODS               //
    //////////////////////////////////////////////

    // print all elements between 2 iterators
    template<class Iterator>
    void disp(Iterator Begin, Iterator End) {
        typedef typename std::iterator_traits<Iterator>::value_type elem;
        for_each(Begin, End, [](elem x) { std::cout << x << "\t"; });
        std::cout << std::endl;
    }

    // print all elements in a container (base case)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> &disp(C<T> &c) {
        for_each(c.begin(), c.end(), [](T x) { std::cout << x << "\t"; });
        std::cout << std::endl;
        return c;
    }

    // print all elements in a container (recursive step)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    void disp(C<C<T>> c) {
        for_each(c.begin(), c.end(), [](C<T> x) { disp(x); });
        std::cout << std::endl;
    }

    // take mean of the elements
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T mean(C<T> &c) {
        return accumulate(c.begin(), c.end(), 0.) / c.size();
    }


    // raise all number in container by alfa
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> &pow(C<T> &v, const T2 alfa) {
        for_each(v.begin(), v.end(), [&](T &x) { x += std::pow(x, alfa); });
        return v;
    }

    // productory of elements in the container
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T prod(C<T> c) {
        return accumulate(c.begin(), c.end(), 1., [](T init, T alfa) { return init * alfa; });
    }

    // standard deviation
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T stdev(C<T> &c) {
        return sqrt(inner_product(c.begin(), c.end(), c.begin(), 0.0) / (c.size()-1) - std::pow(mean(c), 2.));
    }

    // standard deviation (with preprocessed mean)
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T stdev(C<T> &c, T mean) {
        return sqrt(inner_product(c.begin(), c.end(), c.begin(), 0.0) / (c.size()-1) - std::pow(mean, 2.));
    }

    // sum of all elements in the container
    template<template<class B, class All = std::allocator<B> > class C, class T>
    T sum(C<T> c) {
        return accumulate(c.begin(), c.end(), 0.);
    }

}

#endif //MATLAB_METHOD_CONTAINER_UTILS_H
