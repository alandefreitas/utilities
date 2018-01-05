#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <map>
#include <iostream>

#include "utils.h"

using namespace std;
using namespace utl;

namespace boost {
    namespace geometry {
        namespace index {
            template<typename Box>
            struct indexable<boost::shared_ptr<Box> > {
                typedef boost::shared_ptr<Box> V;
                typedef Box const &result_type;
                result_type operator()(V const &v) const { return *v; }
            };
        }
    }
}

template <typename Container>
class my_indexable
{
        typedef typename Container::size_type size_t;
        typedef typename Container::const_reference cref;
        Container const& container;

    public:
        typedef cref result_type;
        explicit my_indexable(Container const& c) : container(c) {}
        result_type operator()(size_t i) const { return container[i]; }
};


int main() {
    cout << bold << on_yellow << "Shortcuts for random numbers" << reset << endl;

    cout << on_yellow << bold << underline << "Uniform Distribution"
         << reset << endl;
    {
        cout << bold << underline << "Floating Point" << reset << endl;
        cout << "rand(): " << rand<double>() << endl;
        cout << "rand(): " << rand<double>() << endl;
        cout << "rand(): " << rand<int>() << endl;
        cout << "rand(): " << rand<int>() << endl;
        cout << "rand(): " << rand() << " (don't use it: ambiguous)" << endl;
        cout << "rand<double>(): " << rand < double > () << endl;
        cout << "rand<double>(): " << rand < double > () << endl;
        cout << "rand(5.0,15.0): " << rand(5.0, 15.0) << endl;
        cout << "rand(5.0,15.0): " << rand(5.0, 15.0) << endl;
        cout << "rand<double>(5.0,15.0): " << rand < double > (5.0, 15.0) << endl;
        cout << "rand<double>(5.0,15.0): " << rand < double > (5.0, 15.0) << endl;
        cout << bold << underline << "Integer" << reset << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "rand<int>(): " << rand < int > () << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(3,15): " << randi(3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10, 3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10, 3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10, 3, 15) << endl;
        cout << "randi(10,3,15): " << randi(10, 3, 15) << endl;
    }

    cout << on_yellow << bold << underline << "Related to Normal distribution"
         << reset << endl;
    {
        cout << bold << underline << "Normal Distribution" << reset << endl;
        cout << "randn(): " << randn() << endl;
        cout << "randn(): " << randn() << endl;
        cout << "randn(4.3,2.5): " << randn(4.3, 2.5) << endl;
        cout << "randn(4.3,2.5): " << randn(4.3, 2.5) << endl;
        cout << "randn(10,4.3,2.5): " << randn(10, 4.3, 2.5) << endl;
        cout << "randn(10,4.3,2.5): " << randn(10, 4.3, 2.5) << endl;
        cout << "randn(4,4,4.3,2.5): " << randn(4, 4, 4.3, 2.5) << endl;
        cout << "randn(4,4,4.3,2.5): " << randn(4, 4, 4.3, 2.5) << endl;
        cout << "randn<double>(4,2): " << randn<double>(4, 2) << endl;
        cout << "randn<double>(4,2): " << randn<double>(4, 2) << endl;
        cout << "randn(4,2): " << randn(4, 2) << endl;
        cout << "randn(4,2): " << randn(4, 2) << endl;
        cout << "randn<int>(4,2): " << randn<int>(4, 2) << endl;
        cout << "randn<int>(4,2): " << randn<int>(4, 2) << endl;
        cout << "normal(3.0,10.0): " << normal(3.0, 10.0) << endl;
        cout << "normal(3.0,10.0): " << normal(3.0, 10.0) << endl;
        cout << "normal(3,10): " << normal(3, 10) << endl;
        cout << "normal(3,10): " << normal(3, 10) << endl;

        cout << bold << underline << "Lognormal distribution" << reset << endl;
        cout << "lognormal(3.0,10.0): " << lognormal(3.0, 10.0) << endl;
        cout << "lognormal(3.0,10.0): " << lognormal(3.0, 10.0) << endl;
        cout << "lognormal(3,10): " << lognormal(3, 10) << endl;
        cout << "lognormal(3,10): " << lognormal(3, 10) << endl;

        cout << bold << underline << "Chi-squared distribution" << reset << endl;
        cout << "chi_squared(10.0): " << chi_squared(10.0) << endl;
        cout << "chi_squared(10.0): " << chi_squared(10.0) << endl;
        cout << "chi_squared(10): " << chi_squared(10) << endl;
        cout << "chi_squared(10): " << chi_squared(10) << endl;

        cout << bold << underline << "Cauchy distribution" << reset << endl;
        cout << "cauchy(1.0,1): " << cauchy(1.0, 1.) << endl;
        cout << "cauchy(1.0,1): " << cauchy(1.0, 1.) << endl;
        cout << "cauchy(1,1): " << cauchy(1, 1) << endl;
        cout << "cauchy(1,1): " << cauchy(1, 1) << endl;

        cout << bold << underline << "Fisher F-distribution" << reset << endl;
        cout << "fisher_f(2.0,2): " << fisher_f(2.0, 2.) << endl;
        cout << "fisher_f(2.0,2): " << fisher_f(2.0, 2.) << endl;
        cout << "fisher_f(2,2): " << fisher_f(2, 2) << endl;
        cout << "fisher_f(2,2): " << fisher_f(2, 2) << endl;

        cout << bold << underline << "Student T-Distribution" << reset << endl;
        cout << "student_t(10.0): " << student_t(10.0) << endl;
        cout << "student_t(10.0): " << student_t(10.0) << endl;
        cout << "student_t(10): " << student_t(10) << endl;
        cout << "student_t(10): " << student_t(10) << endl;


    }

    cout << on_yellow << bold << underline << "Related to Bernoulli (yes/no) trials:"
         << reset << endl;
    {
        cout << bold << underline << "Bernoulli distribution" << reset << endl;
        cout << "bernoulli(0.7): " << bernoulli(0.7) << endl;
        cout << "bernoulli(0.7): " << bernoulli(0.7) << endl;
        cout << "bernoulli(0.3): " << bernoulli(0.3) << endl;
        cout << "bernoulli(0.3): " << bernoulli(0.3) << endl;

        cout << bold << underline << "Binomial distribution" << reset << endl;
        cout << "binomial(100,0.7): " << binomial(100, 0.7) << endl;
        cout << "binomial(100,0.7): " << binomial(100, 0.7) << endl;
        cout << "binomial(100,0.3): " << binomial(100, 0.3) << endl;
        cout << "binomial(100,0.3): " << binomial(100, 0.3) << endl;

        cout << bold << underline << "Geometric distribution" << reset << endl;
        cout << "geometric(0.9): " << geometric(0.9) << endl;
        cout << "geometric(0.9): " << geometric(0.9) << endl;
        cout << "geometric(0.1): " << geometric(0.1) << endl;
        cout << "geometric(0.1): " << geometric(0.1) << endl;

        cout << bold << underline << "Negative binomial distribution" << reset << endl;
        cout << "negative_binomial(100,0.7): " << negative_binomial(100, 0.7) << endl;
        cout << "negative_binomial(100,0.7): " << negative_binomial(100, 0.7) << endl;
        cout << "negative_binomial(100,0.3): " << negative_binomial(100, 0.3) << endl;
        cout << "negative_binomial(100,0.3): " << negative_binomial(100, 0.3) << endl;

    }

    cout << on_yellow << bold << underline << "Rate-based distributions:"
         << reset
         << endl;
    {
        cout << bold << underline << "Poisson distribution" << reset << endl;
        cout << "poisson(1.5): " << poisson(1.5) << endl;
        cout << "poisson(1.5): " << poisson(1.5) << endl;
        cout << "poisson(1.5): " << poisson(1.5) << endl;
        cout << "poisson(1.5): " << poisson(1.5) << endl;

        cout << bold << underline << "Exponential distribution" << reset << endl;
        cout << "exponential(1.5): " << exponential(1.5) << endl;
        cout << "exponential(1.5): " << exponential(1.5) << endl;
        cout << "exponential(1.5): " << exponential(1.5) << endl;
        cout << "exponential(1.5): " << exponential(1.5) << endl;

        cout << bold << underline << "Gamma distribution" << reset << endl;
        cout << "gamma(1.5,1.5): " << gamma(1.5, 1.5) << endl;
        cout << "gamma(1.5,1.5): " << gamma(1.5, 1.5) << endl;
        cout << "gamma(1.5,1.5): " << gamma(1.5, 1.5) << endl;
        cout << "gamma(1.5,1.5): " << gamma(1.5, 1.5) << endl;

        cout << bold << underline << "Weibull distribution" << reset << endl;
        cout << "weibull(1.5,1.5): " << weibull(1.5, 1.5) << endl;
        cout << "weibull(1.5,1.5): " << weibull(1.5, 1.5) << endl;
        cout << "weibull(1.5,1.5): " << weibull(1.5, 1.5) << endl;
        cout << "weibull(1.5,1.5): " << weibull(1.5, 1.5) << endl;

        cout << bold << underline << "Extreme Value distribution" << reset << endl;
        cout << "extreme_value(1.5,1.5): " << extreme_value(1.5, 1.5) << endl;
        cout << "extreme_value(1.5,1.5): " << extreme_value(1.5, 1.5) << endl;
        cout << "extreme_value(1.5,1.5): " << extreme_value(1.5, 1.5) << endl;
        cout << "extreme_value(1.5,1.5): " << extreme_value(1.5, 1.5) << endl;

    }

    cout << on_yellow << bold << underline << "Piecewise distributions:"
         << reset
         << endl;
    {
        cout << bold << underline << "Discrete distribution" << reset << endl;
        cout << "discrete({2,2,1,1,2,2,1,1,2,2}): " << discrete({2, 2, 1, 1, 2, 2, 1, 1, 2, 2}) << endl;
        cout << "discrete({2,2,1,1,2,2,1,1,2,2}): " << discrete({2, 2, 1, 1, 2, 2, 1, 1, 2, 2}) << endl;
        cout << "vector<int> a = {2,2,1,1,2,2,1,1,2,2}; " << endl;
        vector<int> a = {2, 2, 1, 1, 2, 2, 1, 1, 2, 2};
        cout << "discrete(a): " << discrete(a) << endl;
        cout << "discrete(a): " << discrete(a) << endl;
        cout << "discrete({2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}): "
                  << discrete({2.0, 2.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 2.0, 2.0}) << endl;
        cout << "discrete({2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}): "
                  << discrete({2.0, 2.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 2.0, 2.0}) << endl;
        cout << "vector<double> b = {2.0,2.0,1.0,1.0,2.0,2.0,1.0,1.0,2.0,2.0}; " << endl;
        vector<double> b = {2.0, 2.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 2.0, 2.0};
        cout << "discrete(b): " << discrete(b) << endl;
        cout << "discrete(b): " << discrete(b) << endl;

        cout << bold << underline << "Piecewise constant distribution" << reset
             << endl;
        cout << "vector<double> intervals {0.0, 2.0, 4.0, 6.0, 8.0, 10.0};" << endl;
        vector<double> intervals{0.0, 2.0, 4.0, 6.0, 8.0, 10.0};
        cout << "vector<double> weights {2.0, 1.0, 2.0, 1.0, 2.0};" << endl;
        vector<double> weights{2.0, 1.0, 2.0, 1.0, 2.0};
        cout << "piecewise_constant(intervals,weights): " << piecewise_constant(intervals, weights) << endl;
        cout << "piecewise_constant(intervals,weights): " << piecewise_constant(intervals, weights) << endl;
        cout << "piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0},{2.0, 1.0, 2.0, 1.0, 2.0}): "
                  << piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0}, {2.0, 1.0, 2.0, 1.0, 2.0}) << endl;
        cout << "piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0},{2.0, 1.0, 2.0, 1.0, 2.0}): "
                  << piecewise_constant({0.0, 2.0, 4.0, 6.0, 8.0, 10.0}, {2.0, 1.0, 2.0, 1.0, 2.0}) << endl;

        cout << bold << underline << "Piecewise linear distribution" << reset << endl;
        cout << "vector<double> intervals {0.0, 4.5, 9.0};" << endl;
        vector<double> intervals2{0.0, 4.5, 9.0};
        cout << "vector<double> weights {10.0, 0.0, 10.0};" << endl;
        vector<double> weights2{10.0, 0.0, 10.0};
        cout << "piecewise_linear(intervals2,weights2): " << piecewise_linear(intervals2, weights2) << endl;
        cout << "piecewise_linear(intervals2,weights2): " << piecewise_linear(intervals2, weights2) << endl;
        cout << "piecewise_linear({0.0, 4.5, 9.0},{10.0, 0.0, 10.0}): "
                  << piecewise_linear({0.0, 4.5, 9.0}, {10.0, 0.0, 10.0}) << endl;
        cout << "piecewise_linear({0.0, 4.5, 9.0},{10.0, 0.0, 10.0}): "
                  << piecewise_linear({0.0, 4.5, 9.0}, {10.0, 0.0, 10.0}) << endl;

    }

    cout << bold << on_yellow << "Numeric Container Shortcuts for Generating new containers" << reset << endl;
    cout << on_yellow << bold << underline << "Container Generators" << reset << endl;
    {
        cout << bold << underline << "Eye" << reset << endl;
        cout << "eye(3): " << eye(3) << endl;
        cout << "eye<int>(3): " << eye<int>(3) << endl;
        cout << bold << underline << "Linspace" << reset << endl;
        cout << "linspace(3.0,10.0,11.0): " << linspace(3.0, 10.0, 11.0) << endl;
        cout << "linspace<int>(3,10,11): " << linspace<int>(3, 10, 11) << endl;
        cout << bold << underline << "Rand" << reset << endl;
        cout << "rand(10): " << rand(10) << endl;
        cout << "rand(4,4): " << rand(4, 4) << endl;
        cout << "rand(2,3,2): " << rand(2, 3, 2) << endl;
        cout << bold << underline << "Zeros" << reset << endl;
        cout << "zeros(3): " << zeros(3) << endl;
        cout << "zeros(3,3): " << zeros(3, 3) << endl;
        cout << bold << underline << "Ones" << reset << endl;
        cout << "ones(3): " << ones(3) << endl;
        cout << "ones(3,3): " << ones(3, 3) << endl;
        cout << bold << underline << "Perm" << reset << endl;
        cout << "perm(10): " << perm(10) << endl;
        cout << "perm(20): " << perm(20) << endl;
        cout << "perm(30,3): " << perm(30, 3) << endl;
    }

    cout << on_yellow << bold << underline << "Numeric Container Methods and Statistics" << reset << endl;
    {
        cout << bold << underline << "Random numbers" << reset << endl;
        vector<double> a = rand(10);
        disp(a);
        cout << bold << underline << "Statistics" << reset << endl;
        cout << "mean(a): " << mean(a) << endl;
        cout << "stdev(a): " << stdev(a) << endl;
        cout << "stdev(a,mean(a)): " << stdev(a,mean(a)) << endl;
        cout << bold << underline << "Math" << reset << endl;
        cout << "pow(a, 3.2): " << pow(a, 3.2) << endl;
        cout << "prod(a): " << prod(a) << endl;
        cout << "sum(a): " << sum(a) << endl;
    }

    cout << on_yellow << bold << underline << "Operations between numeric containers" << reset << endl;
    {
        cout << bold << underline << "Random numbers" << reset << endl;
        vector<double> a = rand(10);
        cout << "a: " << a << endl;
        vector<double> b = rand(10);
        cout << "b: " << b << endl;
        vector<int> c = ones(20);
        cout << "c: " << c << endl;
        cout << bold << underline << "Operations" << reset << endl;
        cout << "cat(a,b): " << cat(a, b) << endl;
        cout << "copyshape(c,a): " << copyshape(c,a) << endl;
        cout << "inner(a,b): " << inner(a,b) << endl;
    }

    cout << on_yellow << bold << underline
              << "Controlling the size of integers" << reset << endl;
    {
        cout << bold << underline
                  << "boost::int8_t and boost::uint64_t carry the exact memory size in their names" << reset
                  << endl;
        int8_t i8 = 1;
        cout << "sizeof(i8): " << sizeof(i8) << '\n';

        #ifndef BOOST_NO_INT64_T
        uint64_t ui64 = 1;
        cout << "sizeof(ui64): " << sizeof(ui64) << '\n';
        #endif

        cout << bold << underline
                  << "int_least8_t and uint_least32_t contain at least as many bits as their names say"
                  << reset << endl;

        int_least8_t il8 = 1;
        cout << "sizeof(il8): " << sizeof(il8) << '\n';

        uint_least32_t uil32 = 1;
        cout << "sizeof(uil32): " << sizeof(uil32) << '\n';

        cout << bold << underline
                  << "int_fast8_t and uint_fast16_t also have a minimum size. Their actual size is set to a value that guarantees the best performance"
                  << reset << endl;

        int_fast8_t if8 = 1;
        cout << "sizeof(if8): " << sizeof(if8) << '\n';

        uint_fast16_t uif16 = 1;
        cout << "sizeof(uif16): " << sizeof(uif16) << '\n';

        cout << bold << underline
                  << "intmax_t and uintmax_t, for the maximum width integer types available on a platform"
                  << reset << endl;

        intmax_t imax = 1;
        cout << "sizeof(imax): " << sizeof(imax) << '\n';

        cout << "sizeof(UINT8_C(1)): " << sizeof(UINT8_C(1)) << '\n';

        #ifndef BOOST_NO_INT64_T
        cout << "sizeof(INT64_C(1)): " << sizeof(INT64_C(1)) << '\n';
        #endif
    }

    cout << bold << on_yellow << "Numeric Conversion" << reset << endl;
    cout << bold << underline << "Implicit conversion from int to short"
              << reset << endl;
    {
        int i = 0x10000;
        short s = i;
        cout << "s: " << s << '\n';
    }

    cout << bold << underline << "Overflow detection with boost::numeric_cast"
              << reset << endl;
    {
        try {
            int i = 0x10000;
            short s = numeric_cast<short>(i);
            cout << "s: " << s << '\n';
        }
        catch (bad_numeric_cast &e) {
            cerr << "e.what(): " << e.what() << '\n';
        }
    }

    cout << bold << underline << "Overflow detection for negative numbers"
              << reset << endl;
    {
        try {
            int i = -0x10000;
            short s = numeric_cast<short>(i);
            cout << "s: " << s << '\n';
        }
        catch (negative_overflow &e) {
            cerr << "e.what(): " << e.what() << '\n';
        }
    }

    cout << bold << on_yellow << "Basic Linear Algebra Library" << reset << endl;
    cout << bold << underline << "Vector" << reset << endl;
    {
        ublas::vector<double> v(3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        cout << v << endl;
        v -= v * 12;
        cout << v << endl;
    }

    cout << bold << underline << "Unit Vector" << reset << endl;
    {
        for (int i = 0; i < 3; ++i) {
            ublas::unit_vector<double> v(3, i);
            cout << v << endl;
        }
    }

    cout << bold << underline << "Zero Vector" << reset << endl;
    {
        ublas::zero_vector<double> v(3);
        cout << v << endl;
    }

    cout << bold << underline << "Scalar Vector" << reset << endl;
    {
        ublas::scalar_vector<double> v(3);
        cout << v << endl;
    }

    cout << bold << underline << "Mapped Vector" << reset << endl;
    {
        ublas::mapped_vector<double> v(3, 3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        cout << v << endl;
    }

    cout << bold << underline << "Compressed Vector" << reset << endl;
    {
        ublas::compressed_vector<double> v(3, 3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        cout << v << endl;
    }

    cout << bold << underline << "Coordinate Vector" << reset << endl;
    {
        ublas::coordinate_vector<double> v(3, 3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        cout << v << endl;
    }

    cout << bold << underline << "Vector Range" << reset << endl;
    {
        ublas::vector<double> v(3);
        ublas::vector_range<ublas::vector<double> > vr(v, ublas::range(0, 3));
        for (unsigned i = 0; i < vr.size(); ++i) {
            vr(i) = i;
        }
        cout << vr << endl;
    }

    cout << bold << underline << "Generic Projections" << reset << endl;
    {
        ublas::vector<double> v(3);
        for (int i = 0; i < 3; ++i) {
            project(v, ublas::range(0, 3))(i) = i;
        }
        cout << project(v, ublas::range(0, 3)) << endl;
    }

    cout << bold << underline << "Vector Slice" << reset << endl;
    {
        ublas::vector<double> v(3);
        ublas::vector_slice<ublas::vector<double> > vs(v, ublas::slice(0, 1, 3));
        for (unsigned i = 0; i < vs.size(); ++i) {
            vs(i) = i;
        }
        cout << vs << endl;
    }

    cout << bold << underline << "Generic Projections" << reset << endl;
    {
        ublas::vector<double> v(3);
        for (int i = 0; i < 3; ++i) {
            project(v, ublas::slice(0, 1, 3))(i) = i;
        }
        cout << project(v, ublas::slice(0, 1, 3)) << endl;
    }

    cout << bold << on_yellow << "Geometry" << reset << endl;
    cout << on_yellow << bold << underline << "Quick Start" << reset
              << endl;

    cout << bold << underline << "Distance between two points" << reset
              << endl;
    {
        geometry::model::d2::point_xy<int> p1(1, 1), p2(2, 2);
        cout << "Distance p1-p2 is: " << geometry::distance(p1, p2) << endl;
    }

    cout << bold << underline << "Other types as points" << reset << endl;
    {
        int a[2] = {1, 1};
        int b[2] = {2, 3};
        double d = geometry::distance(a, b);
        cout << "Distance a-b is: " << d << endl;
    }

    cout << bold << underline << "Point within polygon" << reset << endl;
    {
        double points[][2] = {{2.0, 1.3},
                              {4.1, 3.0},
                              {5.3, 2.6},
                              {2.9, 0.7},
                              {2.0, 1.3}};
        geometry::model::polygon<geometry::model::d2::point_xy<double> > poly;
        geometry::append(poly, points);
        boost::tuple<double, double> p = boost::make_tuple(3.7, 2.0);
        cout << "Point p is in polygon? " << boolalpha << geometry::within(p, poly) << endl;
        cout << "Area: " << geometry::area(poly) << endl;
        int a[2] = {1, 1};
        double d2 = geometry::distance(a, p);
        cout << "Distance a-p is: " << d2 << endl;
    }

    cout << bold << underline << "Non-Cartesian" << reset << endl;
    {
        // We approximate the Earth as a sphere and calculate the distance between Amsterdam and Paris:
        typedef boost::geometry::model::point
                <double, 2, boost::geometry::cs::spherical_equatorial<boost::geometry::degree>> spherical_point;

        spherical_point amsterdam(4.90, 52.37);
        spherical_point paris(2.35, 48.86);

        double const earth_radius = 3959; // miles
        cout << "Distance in miles: " << distance(amsterdam, paris) * earth_radius << endl;
    }

    cout << on_yellow << bold << underline << "Spatial Indexes"
              << reset
              << endl;


    cout << bold << underline << "R-Tree" << reset << endl;
    {
        typedef geometry::model::point<float, 2, geometry::cs::cartesian> point;
        typedef geometry::model::box<point> box;
        typedef pair<box, unsigned> value;

        // create the rtree using default constructor
        geometry::index::rtree<value, geometry::index::dynamic_rstar> rtree(geometry::index::dynamic_rstar(16));
        // create some values
        for (unsigned i = 0; i < 10; ++i) {
            // create a box
            box b(point(i + 0.0f, i + 0.0f), point(i + 0.5f, i + 0.5f));
            // insert new value
            rtree.insert(make_pair(b, i));
        }
        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        vector<value> result_s;
        rtree.query(geometry::index::intersects(query_box), back_inserter(result_s));
        // find 5 nearest values to a point
        vector<value> result_n;
        rtree.query(geometry::index::nearest(point(0, 0), 5), back_inserter(result_n));
        // display results
        cout << "spatial query box:" << endl;
        cout << geometry::wkt<box>(query_box) << endl;
        cout << "spatial query result:" << endl;
        BOOST_FOREACH(value const &v, result_s) {
                        cout << geometry::wkt<box>(v.first) << " - " << v.second << endl;
                    }

        cout << "knn query point:" << endl;
        cout << geometry::wkt<point>(point(0, 0)) << endl;
        cout << "knn query result:" << endl;
        BOOST_FOREACH(value const &v, result_n) {
                        cout << geometry::wkt<box>(v.first) << " - " << v.second << endl;
                    }

        vector<value> result;
        rtree.query(geometry::index::contains(query_box), back_inserter(result));
        rtree.query(geometry::index::covered_by(query_box), back_inserter(result));
        rtree.query(geometry::index::covers(query_box), back_inserter(result));
        //rtree.query(geometry::index::disjont(query_box), back_inserter(result));
        rtree.query(geometry::index::intersects(query_box), back_inserter(result));
        rtree.query(geometry::index::overlaps(query_box), back_inserter(result));
        rtree.query(geometry::index::within(query_box), back_inserter(result));
        rtree.query(geometry::index::intersects(query_box) && !geometry::index::within(query_box),
                    back_inserter(result));
    }


    cout << bold << underline << "R-tree from vector" << reset << endl;
    {
        typedef geometry::model::point<float, 2, geometry::cs::cartesian> point;
        typedef geometry::model::box<point> box;
        typedef geometry::model::polygon<point, false, false> polygon; // ccw, open polygon
        typedef pair<box, unsigned> value;

        // polygons
        vector<polygon> polygons;

        // create some polygons
        for (unsigned i = 0; i < 10; ++i) {
            // create a polygon
            polygon p;
            for (float a = 0; a < 6.28316f; a += 1.04720f) {
                float x = i + int(10 * ::cos(a)) * 0.1f;
                float y = i + int(10 * ::sin(a)) * 0.1f;
                p.outer().push_back(point(x, y));
            }

            // add polygon
            polygons.push_back(p);
        }

        // display polygons
        cout << "generated polygons:" << endl;
        BOOST_FOREACH(polygon const &p, polygons) {
                        cout << geometry::wkt<polygon>(p) << endl;
                    }

        // create the rtree using default constructor
        geometry::index::rtree<value, geometry::index::rstar<16, 4> > rtree;

        // fill the spatial index
        for (unsigned i = 0; i < polygons.size(); ++i) {
            // calculate polygon bounding box
            box b = geometry::return_envelope<box>(polygons[i]);
            // insert new value
            rtree.insert(make_pair(b, i));
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        vector<value> result_s;
        rtree.query(geometry::index::intersects(query_box), back_inserter(result_s));

        // find 5 nearest values to a point
        vector<value> result_n;
        rtree.query(geometry::index::nearest(point(0, 0), 5), back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // note: the values store the bounding boxes of polygons
        // the polygons aren't used for querying but are printed

        // display results
        cout << "spatial query box:" << endl;
        cout << geometry::wkt<box>(query_box) << endl;
        cout << "spatial query result:" << endl;
        BOOST_FOREACH(value const &v, result_s) {
                        cout << geometry::wkt<polygon>(polygons[v.second]) << endl;
                    }

        cout << "knn query point:" << endl;
        cout << geometry::wkt<point>(point(0, 0)) << endl;
        cout << "knn query result:" << endl;
        BOOST_FOREACH(value const &v, result_n) {
                        cout << geometry::wkt<polygon>(polygons[v.second]) << endl;
                    }
    }

    cout << bold << underline << "Shared pointers to polygons" << reset
              << endl;
    {
        typedef geometry::model::point<float, 2, geometry::cs::cartesian> point;
        typedef geometry::model::box<point> box;
        typedef geometry::model::polygon<point, false, false> polygon; // ccw, open polygon
        typedef boost::shared_ptr<polygon> shp;
        typedef pair<box, shp> value;

        // create the rtree using default constructor
        geometry::index::rtree<value, geometry::index::linear<16, 4> > rtree;

        cout << "filling index with polygons shared pointers:" << endl;

        // create some polygons and fill the spatial index
        for (unsigned i = 0; i < 10; ++i) {
            // create a polygon
            shp p(new polygon());
            for (float a = 0; a < 6.28316f; a += 1.04720f) {
                float x = i + int(10 * ::cos(a)) * 0.1f;
                float y = i + int(10 * ::sin(a)) * 0.1f;
                p->outer().push_back(point(x, y));
            }

            // display new polygon
            cout << geometry::wkt<polygon>(*p) << endl;

            // calculate polygon bounding box
            box b = geometry::return_envelope<box>(*p);
            // insert new value
            rtree.insert(make_pair(b, p));
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        vector<value> result_s;
        rtree.query(geometry::index::intersects(query_box), back_inserter(result_s));

        // find 5 nearest values to a point
        vector<value> result_n;
        rtree.query(geometry::index::nearest(point(0, 0), 5), back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // note: the values store the bounding boxes of polygons
        // the polygons aren't used for querying but are printed

        // display results
        cout << "spatial query box:" << endl;
        cout << geometry::wkt<box>(query_box) << endl;
        cout << "spatial query result:" << endl;
        BOOST_FOREACH(value const &v, result_s) {
                        cout << geometry::wkt<polygon>(*v.second) << endl;
                    }

        cout << "knn query point:" << endl;
        cout << geometry::wkt<point>(point(0, 0)) << endl;
        cout << "knn query result:" << endl;
        BOOST_FOREACH(value const &v, result_n) {
                        cout << geometry::wkt<polygon>(*v.second) << endl;
                    }
    }


    cout << bold << underline << "Iterators of a map storing variant geometries"
              << reset << endl;
    {
        namespace bg = geometry;
        namespace bgi = geometry::index;

        typedef geometry::model::point<float, 2, geometry::cs::cartesian> point;
        typedef geometry::model::box<point> box;
        typedef geometry::model::polygon<point, false, false> polygon; // ccw, open polygon
        typedef geometry::model::ring<point, false, false> ring; // ccw, open ring
        typedef geometry::model::linestring<point> linestring;
        typedef variant<polygon, ring, linestring> geometry;

        typedef map<unsigned, geometry> map;
        typedef pair<box, map::iterator> value;

        auto fill = [](unsigned i, auto &container) {
            for (float a = 0; a < 6.28316f; a += 1.04720f) {
                float x = i + int(10 * ::cos(a)) * 0.1f;
                float y = i + int(10 * ::sin(a)) * 0.1f;
                container.push_back(point(x, y));
            }
        };

        struct print_visitor
                : public boost::static_visitor<> {
            void operator()(polygon const &g) const { cout << boost::geometry::wkt<polygon>(g) << endl; }

            void operator()(ring const &g) const { cout << boost::geometry::wkt<ring>(g) << endl; }

            void operator()(linestring const &g) const { cout << boost::geometry::wkt<linestring>(g) << endl; }
        };

        struct envelope_visitor
                : public boost::static_visitor<box> {
            box operator()(polygon const &g) const { return boost::geometry::return_envelope<box>(g); }

            box operator()(ring const &g) const { return boost::geometry::return_envelope<box>(g); }

            box operator()(linestring const &g) const { return boost::geometry::return_envelope<box>(g); }
        };

        // geometries container
        map geometries;

        // create some geometries
        for (unsigned i = 0; i < 10; ++i) {
            unsigned c = rand() % 3;

            if (0 == c) {
                // create polygon
                polygon p;
                fill(i, p.outer());
                geometries.insert(make_pair(i, geometry(p)));
            } else if (1 == c) {
                // create ring
                ring r;
                fill(i, r);
                geometries.insert(make_pair(i, geometry(r)));
            } else if (2 == c) {
                // create linestring
                linestring l;
                fill(i, l);
                geometries.insert(make_pair(i, geometry(l)));
            }
        }

        // display geometries
        cout << "generated geometries:" << endl;
        BOOST_FOREACH(map::value_type const& p, geometries) {
                        boost::apply_visitor(print_visitor(), p.second);
                    }

        // create the rtree using default constructor
        bgi::rtree<value, bgi::quadratic<16, 4> > rtree;

        // fill the spatial index
        for (map::iterator it = geometries.begin(); it != geometries.end(); ++it) {
            // calculate polygon bounding box
            box b = boost::apply_visitor(envelope_visitor(), it->second);
            // insert new value
            rtree.insert(make_pair(b, it));
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        vector<value> result_s;
        rtree.query(bgi::intersects(query_box), back_inserter(result_s));

        // find 5 nearest values to a point
        vector<value> result_n;
        rtree.query(bgi::nearest(point(0, 0), 5), back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // note: the values store the bounding boxes of geometries
        // the geometries aren't used for querying but are printed

        // display results
        cout << "spatial query box:" << endl;
        cout << bg::wkt<box>(query_box) << endl;
        cout << "spatial query result:" << endl;
        BOOST_FOREACH(value const &v, result_s) {
                        boost::apply_visitor(print_visitor(), v.second->second);
                    }

        cout << "knn query point:" << endl;
        cout << bg::wkt<point>(point(0, 0)) << endl;
        cout << "knn query result:" << endl;
        BOOST_FOREACH(value const &v, result_n) {
                        boost::apply_visitor(print_visitor(), v.second->second);
                    }
    }

    cout << bold << underline
              << "index::indexable function object - storing shared pointers in the rtree" << reset
              << endl;
    {
        typedef geometry::model::point<float, 2, geometry::cs::cartesian> point;
        typedef geometry::model::box<point> box;
        typedef boost::shared_ptr<box> shp;
        typedef shp value;

        // create the rtree using default constructor
        geometry::index::rtree<value, geometry::index::linear<16, 4> > rtree;

        cout << "filling index with boxes shared pointers:" << endl;

        // fill the spatial index
        for (unsigned i = 0; i < 10; ++i) {
            // create a box
            shp b(new box(point(i + 0.0f, i + 0.0f), point(i + 0.5f, i + 0.5f)));

            // display new box
            cout << geometry::wkt<box>(*b) << endl;

            // insert new value
            rtree.insert(b);
        }

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        vector<value> result_s;
        rtree.query(geometry::index::intersects(query_box), back_inserter(result_s));

        // find 5 nearest values to a point
        vector<value> result_n;
        rtree.query(geometry::index::nearest(point(0, 0), 5), back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // display results
        cout << "spatial query box:" << endl;
        cout << geometry::wkt<box>(query_box) << endl;
        cout << "spatial query result:" << endl;
        BOOST_FOREACH(value const &v, result_s) {
                        cout << geometry::wkt<box>(*v) << endl;
                    }

        cout << "knn query point:" << endl;
        cout << geometry::wkt<point>(point(0, 0)) << endl;
        cout << "knn query result:" << endl;
        BOOST_FOREACH(value const &v, result_n) {
                        cout << geometry::wkt<box>(*v) << endl;
                    }
    }

    cout << bold << underline << "Using IndexableGetter function object - storing indexes of external container's elements" << reset << endl;
    {
        typedef geometry::model::point<float, 2, geometry::cs::cartesian> point;
        typedef geometry::model::box<point> box;
        typedef vector<box>::size_type value;
        typedef geometry::index::rstar<16, 4> parameters;
        typedef my_indexable< vector<box> > indexable_getter;

        // boxes
        vector<box> boxes;

        // create some boxes
        for ( unsigned i = 0 ; i < 10 ; ++i )
        {
            // add a box
            boxes.push_back(box(point(i+0.0f, i+0.0f), point(i+0.5f, i+0.5f)));
        }

        // display boxes
        cout << "generated boxes:" << endl;
        BOOST_FOREACH(box const& b, boxes)
                        cout << geometry::wkt<box>(b) << endl;

        // create the rtree
        parameters params;
        indexable_getter ind(boxes);
        geometry::index::rtree<value, parameters, indexable_getter> rtree(params, ind);

        // fill the spatial index
        for ( size_t i = 0 ; i < boxes.size() ; ++i )
            rtree.insert(i);

        // find values intersecting some area defined by a box
        box query_box(point(0, 0), point(5, 5));
        vector<value> result_s;
        rtree.query(geometry::index::intersects(query_box), back_inserter(result_s));

        // find 5 nearest values to a point
        vector<value> result_n;
        rtree.query(geometry::index::nearest(point(0, 0), 5), back_inserter(result_n));

        // note: in Boost.Geometry the WKT representation of a box is polygon

        // display results
        cout << "spatial query box:" << endl;
        cout << geometry::wkt<box>(query_box) << endl;
        cout << "spatial query result:" << endl;
        BOOST_FOREACH(value i, result_s)
                        cout << geometry::wkt<box>(boxes[i]) << endl;

        cout << "knn query point:" << endl;
        cout << geometry::wkt<point>(point(0, 0)) << endl;
        cout << "knn query result:" << endl;
        BOOST_FOREACH(value i, result_n)
                        cout << geometry::wkt<box>(boxes[i]) << endl;
    }

    return 0;
}
