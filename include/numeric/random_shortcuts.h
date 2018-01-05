//
// Created by Alan de Freitas on 03/02/17.
//

#ifndef DATATRANSFORMATION_GENERATOR_H
#define DATATRANSFORMATION_GENERATOR_H


#include <random>
#include <type_traits>

namespace utl {

    ////////////////////////////////////////////////////////////////
    //           Number Generator for all distribuitions          //
    ////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////
    //                 Uniform Distributions                      //
    ////////////////////////////////////////////////////////////////
    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T rand(){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        static std::uniform_real_distribution<T> distribution(0.,1.);
        T result = distribution(generator);
        return result;
    }

    template <typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
    T rand(){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        static std::uniform_int_distribution<T> distribution(0,1);
        T result = distribution(generator);
        return result;
    }

    template <class T = double>
    T rand(T lower_bound, T upper_bound){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::uniform_real_distribution<T>(lower_bound,upper_bound)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T randi(T lower_bound, T upper_bound = std::numeric_limits<T>::max() ){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::uniform_int_distribution<T>(lower_bound,upper_bound)(generator);
    }

    template <typename T = int>
    std::vector<T> randi(long size, T lb = 0, T ub = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        static std::uniform_int_distribution<T> distribution(lb,ub);
        std::vector<T> result(size);
        for_each(result.begin(),result.end(),[&](T &x){x = distribution(generator);});
        return result;
    }


    ////////////////////////////////////////////////////////////////
    //              Related to Normal distribution                //
    ////////////////////////////////////////////////////////////////

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T normal(T mean = 0, T stddev = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::normal_distribution<T>(mean,stddev)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T normal(T mean = 0, T stddev = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::normal_distribution<double>(mean,stddev)(generator);
    }

    template <typename T = double>
    T randn(){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        static std::normal_distribution<T> distribution(0,1);
        T result = distribution(generator);
        return result;
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T randn(T mean = 0, T stddev = 1){
        return normal(mean,stddev);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T randn(T mean = 0, T stddev = 1){
        return normal(mean,stddev);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    std::vector<T> randn(long size, T mean = 0, T stddev = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        static std::normal_distribution<T> distribution(mean,stddev);
        std::vector<T> result(size);
        std::for_each(result.begin(),result.end(),[&](T &x){x = distribution(generator);});
        return result;
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    std::vector<std::vector<T>> randn(long n_rows, long n_cols, T mean = 0, T stddev = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        static std::normal_distribution<T> distribution(mean,stddev);
        std::vector<std::vector<T>> result(n_rows);
        std::for_each(result.begin(),result.end(),[&](std::vector<T> &x){x = randn(n_cols,mean,stddev);});
        return result;
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T lognormal(T mean = 0, T stddev = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::lognormal_distribution<T>(mean,stddev)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T lognormal(T mean = 0, T stddev = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::lognormal_distribution<double>(mean,stddev)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T chi_squared(T degrees_of_freedom = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::chi_squared_distribution<T>(degrees_of_freedom)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T chi_squared(T degrees_of_freedom = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::chi_squared_distribution<double>(degrees_of_freedom)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T cauchy(T peak_location = 0, T scale = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::cauchy_distribution<T>(peak_location,scale)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T cauchy(T peak_location = 0, T scale = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::cauchy_distribution<double>(peak_location,scale)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T fisher_f(T degrees_of_freedom_numerator = 2, T degrees_of_freedom_denominator = 2){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::fisher_f_distribution<T>(degrees_of_freedom_numerator,degrees_of_freedom_denominator)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T fisher_f(T degrees_of_freedom_numerator = 2, T degrees_of_freedom_denominator = 2){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::fisher_f_distribution<double>(degrees_of_freedom_numerator,degrees_of_freedom_denominator)(generator);
    }

    template <typename T, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T student_t(T degrees_of_freedom = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::student_t_distribution<T>(degrees_of_freedom)(generator);
    }

    template <typename T, std::enable_if_t<std::is_integral<T>::value>* = nullptr>
    T student_t(T degrees_of_freedom = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::student_t_distribution<double>(degrees_of_freedom)(generator);
    }

    ////////////////////////////////////////////////////////////////
    //           Related to Bernoulli (yes/no) trials             //
    ////////////////////////////////////////////////////////////////

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    bool bernoulli(T probability = 1){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::bernoulli_distribution(probability)(generator);
    }

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I binomial(I trials = 10, T probability = 0.5){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::binomial_distribution<I>(trials,probability)(generator);
    };

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I geometric(T probability = 0.5){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::geometric_distribution<I>(probability)(generator);
    };

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I negative_binomial(I unsuccessful_trials = 10, T probability = 0.5){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::negative_binomial_distribution<I>(unsuccessful_trials,probability)(generator);
    };


    ////////////////////////////////////////////////////////////////
    //                Rate-based distributions                    //
    ////////////////////////////////////////////////////////////////

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I poisson(T mean = 1.0){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::poisson_distribution<I>(mean)(generator);
    };

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T exponential(T rate_of_occurrence = 1.0){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::exponential_distribution<T>(rate_of_occurrence)(generator);
    }

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T gamma(T alpha_shape = 1.0, T beta_scale = 1.0){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::gamma_distribution<T>(alpha_shape,beta_scale)(generator);
    }

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T weibull(T alpha_shape = 1.0, T beta_scale = 1.0){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::weibull_distribution<T>(alpha_shape,beta_scale)(generator);
    }

    template <typename T = double, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
    T extreme_value(T alpha_location = 0.0, T beta_scale = 1.0){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::extreme_value_distribution<T>(alpha_location,beta_scale)(generator);
    }

    ////////////////////////////////////////////////////////////////
    //                Piecewise distributions                     //
    ////////////////////////////////////////////////////////////////

    template <typename T = double, typename I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const std::initializer_list<T> l){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::discrete_distribution<T>(l)(generator);
    }

    template <typename T = int, typename I = int, std::enable_if_t<std::is_integral<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const std::initializer_list<T> l){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::discrete_distribution<T>(l.begin(),l.end())(generator);
    }

    template<template<class B, class All = std::allocator<B> > class C, class T = double, class I = int, std::enable_if_t<std::is_floating_point<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const C<T>& c) {
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::discrete_distribution<T>(c.begin(),c.end())(generator);
    }

    template<template<class B, class All = std::allocator<B> > class C, class T = double, class I = int, std::enable_if_t<std::is_integral<T>::value>* = nullptr, std::enable_if_t<std::is_integral<I>::value>* = nullptr>
    I discrete(const C<T>& c) {
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::discrete_distribution<T>(c.begin(),c.end())(generator);
    }


    template <typename T = double, typename I = int>
    I piecewise_constant(const std::initializer_list<T> intervals, const std::initializer_list<T> weights){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::piecewise_constant_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }

    template <template<class B, class All = std::allocator<B> > class C, typename T = double, typename I = int>
    I piecewise_constant(const C<T> intervals, const C<T> weights){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::piecewise_constant_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }

    template <typename T = double, typename I = int>
    I piecewise_linear(const std::initializer_list<T> intervals, const std::initializer_list<T> weights){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::piecewise_linear_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }

    template <template<class B, class All = std::allocator<B> > class C, typename T = double, typename I = int>
    I piecewise_linear(const C<T> intervals, const C<T> weights){
        static std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        return std::piecewise_linear_distribution<T>(intervals.begin(),intervals.end(),weights.begin())(generator);
    }
};


#endif //DATATRANSFORMATION_GENERATOR_H
