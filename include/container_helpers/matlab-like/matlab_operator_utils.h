//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef MATLAB_OPERATOR_CONTAINER_UTILS_H
#define MATLAB_OPERATOR_CONTAINER_UTILS_H

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
    //      OPERATIONS BETWEEN CONTAINERS       //
    //////////////////////////////////////////////

    // concatenate containers
    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<T> cat(C<T> &v1, C<T> &v2) {
        C<T> v3 = v1;
        std::copy(v2.begin(), v2.end(), std::back_inserter(v3));
        return v3;
    }

    // create another container with same size in every dimension (base case)
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T2> &copyshape(C<T> &from, C<T2> &to) {
        to.resize(from.size());
        return to;
    }

    // create another container with same size in every dimension (recursive step)
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T2>> &copyshape(C<C<T>> &from, C<C<T2>> &to) {
        to.resize(from.size());
        typename C<C<T>>::iterator i = from.begin();
        std::for_each(to.begin(), to.end(), [&](C<T> &x) {
            copyshape(*i, x);
            i++;
        });
        return to;
    }

    // inner product of two containers
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    T2 inner(C<T> &v, C<T2> &v2) {
        return inner_product(v.begin(), v.end(), v2.begin(), 0.0);
    }

}

#endif //MATLAB_OPERATOR_CONTAINER_UTILS_H
