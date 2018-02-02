//
// Created by Alan de Freitas on 03/02/17.
//

#ifndef UTILITIES_STATISTICS_H
#define UTILITIES_STATISTICS_H

#include <vector>

#include <math.h>
#include <cmath>
#include <algorithm>
#include <iterator>

#include <boost/math/constants/constants.hpp>
#include <boost/math/distributions.hpp>

#include "../paradigms/traits.hpp"

namespace utl {
    /*
     * Descriptive statistics
     */
    template <typename iterator>
    inline double mean(typename std::enable_if<utl::is_iterator<iterator>::value,iterator>::type begin, iterator end){
        return std::accumulate(begin,end,0.0)/std::distance(begin,end);
    }

    template <typename range>
    inline double mean(typename std::enable_if<utl::is_container<range>::value,range>::type r){
        return mean(std::begin(r),std::end(r));
    }

    template <typename iterator>
    inline double std_dev(typename std::enable_if<utl::is_iterator<iterator>::value,iterator>::type begin, iterator end){
        auto m = mean(begin,end);
        return sqrt(std::accumulate(begin,end,0.0,[m](auto x, auto y){return x+std::pow(y-m,2);})/(std::distance(begin,end)-1));
    }

    template <typename range>
    inline double std_dev(range r){
        return std_dev(std::begin(r),std::end(r));
    }

    template <class Container>
    std::vector<size_t> sorted_origin(const Container &v){
        // allocate std::vector for ranks
        std::vector<size_t> sorted_indexes(v.size());
        // insert 0,1,2,3,4...n-1
        size_t i = 0;
        std::for_each(sorted_indexes.begin(), sorted_indexes.end(), [&i](auto& elem)
        {
            elem = i++;
        });
        // "sort" by reference
        std::sort(sorted_indexes.begin(),sorted_indexes.end(),[&v](auto x, auto y){return v[x] < v[y];});
        // return
        return sorted_indexes;
    }

    template <class Container>
    std::vector<size_t> rank(const Container &v){
        // which elements would be in the sorted array
        auto indexes = sorted_origin(v);
        // puts it in a new array
        std::vector<size_t> ranks(v.size());
        for (int i = 0; i < v.size(); ++i) {
            ranks[indexes[i]] = i;
        }
        // return
        return ranks;
    }

    template <class Container>
    std::vector<size_t> ranks(const Container &v) {
        // which elements would be in the sorted array
        return utl::rank(v);
    }

    template <class Container>
    std::vector<size_t> ranking(const Container &v) {
        // which elements would be in the sorted array
        return utl::rank(v);
    }

    /*
         * PDFS
         */

    inline double arcsine_pdf(double x, double x_min = 0.0, double x_max = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::arcsine_distribution<double>(x_min,x_max),(x-mu)/sigma);
    }

    inline double bernoulli_pdf(double x, double p = 0.5, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::bernoulli_distribution<double>(p),(x-mu)/sigma);
    }

    inline double beta_pdf(double x, double l_alpha = 1.0, double l_beta = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::beta_distribution<double>(l_alpha, l_beta),(x-mu)/sigma);
    }

    inline double binomial_pdf(double x, double n = 1.0, double p = 0.5, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::binomial_distribution<double>(n,p),(x-mu)/sigma);
    }

    inline double cauchy_pdf(double x, double l_location = 0.0, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::cauchy_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double chi_squared_pdf(double x, double i, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::chi_squared_distribution<double>(i),(x-mu)/sigma);
    }

    inline double exponential_pdf(double x, double l_lambda = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::exponential_distribution<double>(l_lambda),(x-mu)/sigma);
    }

    inline double extreme_value_pdf(double x, double a = 0, double b = 1, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::extreme_value_distribution<double>(a,b),(x-mu)/sigma);
    }

    inline double fisher_f_pdf(double x, double i, double j, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::fisher_f_distribution<double>(i,j),(x-mu)/sigma);
    }

    inline double gamma_pdf(double x, double l_shape, double l_scale = 1, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::gamma_distribution<double>(l_shape,l_scale),(x-mu)/sigma);
    }

    inline double geometric_pdf(double x, double p, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::geometric_distribution<double>(p),(x-mu)/sigma);
    }

    template <typename T>
    inline double hyperexponential_pdf(double x, T range, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::hyperexponential_distribution<double>(range),(x-mu)/sigma);
    }

    inline double hypergeometric_pdf(double x, unsigned int r, unsigned int n, unsigned int N, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::hypergeometric_distribution<double>(r,n,N),(x-mu)/sigma);
    }

    inline double inverse_chi_squared_pdf(double x, double df = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::inverse_chi_squared_distribution<double>(df),(x-mu)/sigma);
    }

    inline double inverse_gamma_pdf(double x, double l_shape = 1.0,double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::inverse_gamma_distribution<double>(l_shape,l_scale),(x-mu)/sigma);
    }

    inline double inverse_gaussian_pdf(double x, double l_mean = 1.0, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::inverse_gaussian_distribution<double>(l_mean,l_scale),(x-mu)/sigma);
    }

    inline double laplace_pdf(double x, double l_location = 0.0, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::laplace_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double logistic_pdf(double x, double l_location = 0.0,double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::logistic_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double lognormal_pdf(double x, double l_location = 0.0,double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::lognormal_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double negative_binomial_pdf(double x, double r, double p, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::negative_binomial_distribution<double>(r,p),(x-mu)/sigma);
    }

    inline double non_central_chi_squared_pdf(double x, double df, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::non_central_chi_squared_distribution<double>(df,lambda),(x-mu)/sigma);
    }

    inline double non_central_beta_pdf(double x, double a, double b, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::non_central_beta_distribution<double>(a,b,lambda),(x-mu)/sigma);
    }

    inline double non_central_f_pdf(double x, double v1, double v2, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::non_central_f_distribution<double>(v1,v2,lambda),(x-mu)/sigma);
    }

    inline double non_central_t_pdf(double x, double v, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::non_central_t_distribution<double>(v,lambda),(x-mu)/sigma);
    }

    inline double normal_pdf(double x, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::normal_distribution<double>(),(x-mu)/sigma);
    }

    inline double pareto_pdf(double x, double l_scale = 1.0,double l_shape = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::pareto_distribution<double>(l_scale,l_shape),(x-mu)/sigma);
    }

    inline double poisson_pdf(double x, double l_mean =1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::poisson_distribution<double>(l_mean),(x-mu)/sigma);
    }

    inline double rayleigh_pdf(double x, double l_sigma = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::rayleigh_distribution<double>(l_sigma),(x-mu)/sigma);
    }

    inline double skew_normal_pdf(double x, double l_location = 0.0, double l_scale = 1.0, double l_shape = 0.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::skew_normal_distribution<double>(l_location,l_scale,l_shape),(x-mu)/sigma);
    }

    inline double students_t_pdf(double x, double df, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::students_t_distribution<double>(df),(x-mu)/sigma);
    }

    inline double triangular_pdf(double x, double l_lower = -1.0, double l_mode = 0.0, double l_upper = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::triangular_distribution<double>(l_lower,l_mode,l_upper),(x-mu)/sigma);
    }

    inline double uniform_pdf(double x, double l_lower = 0.0,double l_upper = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::uniform_distribution<double>(l_lower,l_upper),(x-mu)/sigma);
    }

    inline double weibull_pdf(double x, double l_shape, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::pdf(boost::math::weibull_distribution<double>(l_shape,l_scale),(x-mu)/sigma);
    }

    /*
     * CDFS
     */

    inline double arcsine_cdf(double x, double x_min = 0.0, double x_max = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::arcsine_distribution<double>(x_min,x_max),(x-mu)/sigma);
    }

    inline double bernoulli_cdf(double x, double p = 0.5, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::bernoulli_distribution<double>(p),(x-mu)/sigma);
    }

    inline double beta_cdf(double x, double l_alpha = 1.0, double l_beta = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::beta_distribution<double>(l_alpha, l_beta),(x-mu)/sigma);
    }

    inline double binomial_cdf(double x, double n = 1.0, double p = 0.5, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::binomial_distribution<double>(n,p),(x-mu)/sigma);
    }

    inline double cauchy_cdf(double x, double l_location = 0.0, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::cauchy_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double chi_squared_cdf(double x, double i, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::chi_squared_distribution<double>(i),(x-mu)/sigma);
    }

    inline double exponential_cdf(double x, double l_lambda = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::exponential_distribution<double>(l_lambda),(x-mu)/sigma);
    }

    inline double extreme_value_cdf(double x, double a = 0, double b = 1, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::extreme_value_distribution<double>(a,b),(x-mu)/sigma);
    }

    inline double fisher_f_cdf(double x, double i, double j, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::fisher_f_distribution<double>(i,j),(x-mu)/sigma);
    }

    inline double gamma_cdf(double x, double l_shape, double l_scale = 1, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::gamma_distribution<double>(l_shape,l_scale),(x-mu)/sigma);
    }

    inline double geometric_cdf(double x, double p, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::geometric_distribution<double>(p),(x-mu)/sigma);
    }

    template <typename T>
    inline double hyperexponential_cdf(double x, T range, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::hyperexponential_distribution<double>(range),(x-mu)/sigma);
    }

    inline double hypergeometric_cdf(double x, unsigned int r, unsigned int n, unsigned int N, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::hypergeometric_distribution<double>(r,n,N),(x-mu)/sigma);
    }

    inline double inverse_chi_squared_cdf(double x, double df = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::inverse_chi_squared_distribution<double>(df),(x-mu)/sigma);
    }

    inline double inverse_gamma_cdf(double x, double l_shape = 1.0,double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::inverse_gamma_distribution<double>(l_shape,l_scale),(x-mu)/sigma);
    }

    inline double inverse_gaussian_cdf(double x, double l_mean = 1.0, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::inverse_gaussian_distribution<double>(l_mean,l_scale),(x-mu)/sigma);
    }

    inline double laplace_cdf(double x, double l_location = 0.0, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::laplace_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double logistic_cdf(double x, double l_location = 0.0,double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::logistic_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double lognormal_cdf(double x, double l_location = 0.0,double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::lognormal_distribution<double>(l_location,l_scale),(x-mu)/sigma);
    }

    inline double negative_binomial_cdf(double x, double r, double p, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::negative_binomial_distribution<double>(r,p),(x-mu)/sigma);
    }

    inline double non_central_chi_squared_cdf(double x, double df, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::non_central_chi_squared_distribution<double>(df,lambda),(x-mu)/sigma);
    }

    inline double non_central_beta_cdf(double x, double a, double b, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::non_central_beta_distribution<double>(a,b,lambda),(x-mu)/sigma);
    }

    inline double non_central_f_cdf(double x, double v1, double v2, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::non_central_f_distribution<double>(v1,v2,lambda),(x-mu)/sigma);
    }

    inline double non_central_t_cdf(double x, double v, double lambda, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::non_central_t_distribution<double>(v,lambda),(x-mu)/sigma);
    }

    inline double normal_cdf(double x, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::normal_distribution<double>(),(x-mu)/sigma);
    }

    inline double pareto_cdf(double x, double l_scale = 1.0,double l_shape = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::pareto_distribution<double>(l_scale,l_shape),(x-mu)/sigma);
    }

    inline double poisson_cdf(double x, double l_mean =1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::poisson_distribution<double>(l_mean),(x-mu)/sigma);
    }

    inline double rayleigh_cdf(double x, double l_sigma = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::rayleigh_distribution<double>(l_sigma),(x-mu)/sigma);
    }

    inline double skew_normal_cdf(double x, double l_location = 0.0, double l_scale = 1.0, double l_shape = 0.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::skew_normal_distribution<double>(l_location,l_scale,l_shape),(x-mu)/sigma);
    }

    inline double students_t_cdf(double x, double df, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::students_t_distribution<double>(df),(x-mu)/sigma);
    }

    inline double triangular_cdf(double x, double l_lower = -1.0, double l_mode = 0.0, double l_upper = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::triangular_distribution<double>(l_lower,l_mode,l_upper),(x-mu)/sigma);
    }

    inline double uniform_cdf(double x, double l_lower = 0.0,double l_upper = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::uniform_distribution<double>(l_lower,l_upper),(x-mu)/sigma);
    }

    inline double weibull_cdf(double x, double l_shape, double l_scale = 1.0, double mu = 0.0, double sigma = 1.0){
        return boost::math::cdf(boost::math::weibull_distribution<double>(l_shape,l_scale),(x-mu)/sigma);
    }

    /*
     * Confidence limits
     */

    inline double students_t_confidence_limits(double _mean, double _std_dev, long _sample_size, double alpha = 0.05, double mu = 0.0, double sigma = 1.0){
        boost::math::students_t_distribution<double> dist(_sample_size - 1);
        double T = boost::math::quantile(boost::math::complement(dist, alpha / 2));
        return T * _std_dev / sqrt(double(_sample_size));
    }

    /*
     * Hypothesis tests
     */

    // One-sample t-test
    template <typename iterator>
    inline double students_t_test(typename std::enable_if<utl::is_iterator<iterator>::value,iterator>::type begin, iterator end, double true_mean = 0.0){
        auto n = std::distance(begin,end);
        auto t = utl::mean(begin,end)-true_mean/(std_dev(begin,end)/sqrt(n));
        return students_t_pdf(t,n-1);
    }

    template <typename range>
    inline double students_t_test(range r){
        return students_t_test(std::begin(r),std::end(r),0.0);
    }

    // Independent two-sample t-test
    template <typename iterator>
    inline double students_t_test(typename std::enable_if<utl::is_iterator<iterator>::value,iterator>::type begin1, iterator end1, iterator begin2, iterator end2, bool assume_equal_variance = false){
        auto n1 = std::distance(begin1,end1);
        auto n2 = std::distance(begin2,end2);
        if (assume_equal_variance) {
            auto sp = sqrt(((n1 - 1) * std::pow(std_dev(begin1,end1),2.0)+ (n2 - 1) * std::pow(std_dev(begin2,end2),2.0))/(n1+n2-2));
            auto t = utl::mean(begin1,end1) - utl::mean(begin2,end2)/(sp*sqrt(1.0/n1 + 1.0/n2));
            return students_t_pdf(t,n1+n2-2);
        } else {
            // Welch's t-test
            auto s_delta = sqrt(std::pow(std_dev(begin1,end1),2.0)/n1 + std::pow(std_dev(begin2,end2),2.0)/n2);
            auto t = utl::mean(begin1,end1) - utl::mean(begin2,end2) / (s_delta);
            return students_t_pdf(t,n1+n2-2);
        }
    }

    template <typename range>
    inline double students_t_test(range r1, range r2, bool assume_equal_variance = false){
        return students_t_test(std::begin(r1),std::end(r1),std::begin(r2),std::end(r2), assume_equal_variance);
    }

}

#endif //UTILITIES_STATISTICS_H
