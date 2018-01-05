//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef MATLAB_GENERATOR_CONTAINER_UTILS_H
#define MATLAB_GENERATOR_CONTAINER_UTILS_H


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
#include <stdio.h>

namespace utl {

    //////////////////////////////////////////////
    //         CONTAINER GENERATORS             //
    //////////////////////////////////////////////

    // create diagonal matrix
    template<typename T = double>
    std::vector<std::vector<T>> eye(long size) {
        std::vector<std::vector<T>> result(size, std::vector<T>(size, 0));
        for (int i = 0; i < size; i++) {
            result[i][i] = 1;
        }
        return result;
    }

    // generate std::vector with size linearly spaced elements
    template<typename T = double>
    std::vector<T> linspace(T lb, T ub, long size) {
        std::vector<T> result(size);
        double step = (double)(ub - lb) / (double)(size - 1);
        for (int i = 0; i < size; i++) {
            result[i] = (T)(lb + step * i);
        }
        return result;
    }

    // matrix NXM (std::vector of std::vectors) with ones
    template<typename T = double>
    std::vector<std::vector<T>> ones(long rows, long cols) {
        return std::vector<std::vector<T>>(rows, std::vector<T>(cols, 1));
    }

    template<typename T = double>
    std::vector<std::vector<T>> zeros(long rows, long cols) {
        return std::vector<std::vector<T>>(rows, std::vector<T>(cols, 0));
    }

    template<typename T = double>
    std::vector<T> ones(T n) {
        return std::vector<T>(n, 1);
    }

    template<typename T = double>
    std::vector<T> zeros(T n) {
        return std::vector<T>(n, 0);
    }

    template<typename T = int>
    std::vector<T> perm(T n) {
        std::vector<T> r(n);
        for (int i = 0; i < n; ++i) {
            r[i] = i;
        }
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        shuffle(r.begin(),r.end(),generator);
        return r;
    }

    template <typename T = int>
    std::vector<T> perm(long size, T initial = 0){
        std::vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = initial++;});
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        shuffle(result.begin(),result.end(),generator);
        return result;
    }

    // generate a random number with distribution [0,1]
    template<typename T = double>
    std::vector<T> rand(long size) {
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        static std::uniform_real_distribution<T> distribution(0.0, 1.0);
        std::vector<T> result(size);
        for_each(result.begin(), result.end(), [](T &x) { x = distribution(generator); });
        return result;
    }

    // generate matrix of random numbers with distribution [0,1]
    template<typename T = double>
    std::vector<std::vector<T>> rand(long n_rows, long n_cols) {
        std::uniform_real_distribution<T> distribution(0, 1);
        std::vector<std::vector<T>> result(n_rows);
        for_each(result.begin(), result.end(), [&](std::vector<T> &x) { x = rand(n_cols); });
        return result;
    }

    // generate 3d matrix of random numbers distribution [0,1]
    template<typename T = double>
    std::vector<std::vector<std::vector<T>>> rand(long n_rows, long n_cols, long slices) {
        std::uniform_real_distribution<T> distribution(0, 1);
        std::vector<std::vector<std::vector<T>>> result(n_rows);
        for_each(result.begin(), result.end(), [&](std::vector<std::vector<T>> &x) { x = rand(n_cols, slices); });
        return result;
    }

}

#endif //MATLAB_GENERATOR_CONTAINER_UTILS_H
