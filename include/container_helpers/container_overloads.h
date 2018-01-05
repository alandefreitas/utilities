//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_CONTAINER_OVERLOADS_H
#define WPP_CONTAINER_OVERLOADS_H

#include <iostream>
#include <string>
#include <stdio.h>

#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>
#include "prettyprint.hpp"

namespace utl {

    ///////////////////////////////////////////
    //           NUMERIC OPERATORS           //
    ///////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator+(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::plus<T>());
        } else {
            std::cerr << "The containers should have the same size" << std::endl;
        }
        return result;
    }
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator-(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::minus<T>());
        } else {
            std::cerr << "The containers should have the same size" << std::endl;
        }
        return result;
    }
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator*(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::multiplies<T>());
        } else {
            std::cerr << "The containers should have the same size" << std::endl;
        }
        return result;
    }
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator/(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::divides<T>());
        } else {
            std::cerr << "The containers should have the same size" << std::endl;
        }
        return result;
    }
    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator%(const C<T>& a, const C<T2> b) {
        C<T> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::modulus<T>());
        } else {
            std::cerr << "The containers should have the same size" << std::endl;
        }
        return result;
    }

    ///////////////////////////////////////////
    //       NUMERIC OPERATORS (+SCALAR)     //
    ///////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator+(const C<T>& v, const T2 alfa) {
        C<T> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](T &x){x += (T) alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator-(const C<T> &v, const T2 alfa) {
        C<T> result(v.begin(), v.end());
        std::for_each(result.begin(), result.end(), [&](T &x) { x -= (T) alfa; });
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator*(const C<T> &v, const T2 alfa) {
        C<T> result(v.begin(), v.end());
        std::for_each(result.begin(), result.end(), [&](T &x) { x *= (T) alfa; });
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator/(const C<T> &v, const T2 alfa) {
        C<T> result(v.begin(), v.end());
        std::for_each(result.begin(), result.end(), [&](T &x) { x /= (T) alfa; });
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T> operator%(const C<T>& v, const T2 alfa) {
        C<T> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](T &x){x %= (T) alfa;});
        return result;
    }

    ///////////////////////////////////////////
    //         NUMERICAL ATTRIBUTION         //
    ///////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator+=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::plus<T>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator-=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::minus<T>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator*=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::multiplies<T>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator/=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::divides<T>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator%=(C<T>& a, const C<T2> b) {
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::modulus<T>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    ///////////////////////////////////////////
    //     NUMERICAL ATTRIBUTION (SCALAR)    //
    ///////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator+=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x += alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator-=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x -= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator*=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x *= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator/=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x /= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<T>& operator%=(C<T>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](T &x){x %= alfa;});
        return v;
    }

    ////////////////////////////////////////
    //     2-DIMENSIONAL CONTAINERS       //
    ////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator+(const C<C<T>>& a, const C<C<T2>> b) {
        C<C<T>> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::plus<C<T>>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator-(const C<C<T>>& a, const C<C<T2>> b) {
        C<C<T>> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::minus<C<T>>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator*(const C<C<T>>& a, const C<C<T2>> b) {
        C<C<T>> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::multiplies<C<T>>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator/(const C<C<T>>& a, const C<C<T2>> b) {
        C<C<T>> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::divides<C<T>>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator%(const C<C<T>>& a, const C<C<T2>> b) {
        C<C<T>> result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::modulus<C<T>>());
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return result;
    }

    ////////////////////////////////////////
    //  2-DIMENSIONAL CONTAINERS (SCALAR) //
    ////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator+(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x += alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator-(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x -= alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator*(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x *= alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator/(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x /= alfa;});
        return result;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>> operator%(const C<C<T>>& v, const T2 alfa) {
        C<C<T>> result(v.begin(),v.end());
        std::for_each(result.begin(),result.end(),[&](C<T> &x){x %= alfa;});
        return result;
    }

    ////////////////////////////////////////
    //      2-D NUMERICAL ATTRIBUTION     //
    ////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator+=(C<C<T>>& a, const C<C<T2>> b) {
        const auto func = [](C<T> a, C<T> b){return a + b;};
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(), a.begin(), func);
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator-=(C<C<T>>& a, const C<C<T2>> b) {
        const auto func = [](C<T> a, C<T> b){return a - b;};
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(), a.begin(), func);
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator*=(C<C<T>>& a, const C<C<T2>> b) {
        const auto func = [](C<T> a, C<T> b){return a * b;};
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(), a.begin(), func);
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator/=(C<C<T>>& a, const C<C<T2>> b) {
        const auto func = [](C<T> a, C<T> b){return a / b;};
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(), a.begin(), func);
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator%=(C<C<T>>& a, const C<C<T2>> b) {
        const auto func = [](C<T> a, C<T> b){return a % b;};
        if (a.size() == b.size()){
            transform(a.begin(), a.end(), b.begin(), a.begin(), func);
        } else {
            std::cout << "The containers should have the same size" << std::endl;
        }
        return a;
    }

    ////////////////////////////////////////
    // 2-D NUMERICAL ATTRIBUTION (SCALAR) //
    ////////////////////////////////////////

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator+=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x += alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator-=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x -= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator*=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x *= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator/=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x /= alfa;});
        return v;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T, class T2>
    C<C<T>>& operator%=(C<C<T>>& v, const T2 alfa) {
        std::for_each(v.begin(),v.end(),[&](C<T> &x){x %= alfa;});
        return v;
    }

}

#endif //WPP_CONTAINER_OVERLOADS_H
