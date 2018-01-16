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
#include "../paradigms/traits.hpp"

namespace utl {

    ///////////////////////////////////////////
    //           NUMERIC OPERATORS           //
    ///////////////////////////////////////////

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type
    addition(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            std::transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::plus<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type
    subtraction(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            std::transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::minus<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type
    multiplication(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            std::transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::multiplies<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type
    division(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            std::transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::divides<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type
    module(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            std::transform(a.begin(), a.end(), b.begin(),
                      std::back_inserter(result), std::modulus<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    ///////////////////////////////////////////
    //       NUMERIC OPERATORS (+SCALAR)     //
    ///////////////////////////////////////////

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    addition(Container & a, Scalar alfa) {
        Container result(a.begin(),a.end());
        std::for_each(result.begin(),result.end(),[&](typename Container::value_type &x){x += (typename Container::value_type) alfa;});
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    subtraction(typename std::enable_if<utl::is_container_of_scalar<Container>::value,Container>::type & a,
                   typename std::enable_if<std::is_scalar<Scalar>::value,Scalar>::type alfa) {
        Container result(a.begin(), a.end());
        std::for_each(result.begin(), result.end(), [&](typename Container::value_type &x) { x -= (typename Container::value_type) alfa; });
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    multiplication(typename std::enable_if<utl::is_container_of_scalar<Container>::value,Container>::type & a,
                         typename std::enable_if<std::is_scalar<Scalar>::value,Scalar>::type alfa) {
        Container result(a.begin(), a.end());
        std::for_each(result.begin(), result.end(), [&](typename Container::value_type &x) { x *= (typename Container::value_type) alfa; });
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    division(typename std::enable_if<utl::is_container_of_scalar<Container>::value,Container>::type & a,
                      typename std::enable_if<std::is_scalar<Scalar>::value,Scalar>::type alfa) {
        Container result(a.begin(), a.end());
        std::for_each(result.begin(), result.end(), [&](typename Container::value_type &x) { x /= (typename Container::value_type) alfa; });
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    module(typename std::enable_if<utl::is_container_of_scalar<Container>::value,Container>::type & a,
                      typename std::enable_if<std::is_scalar<Scalar>::value,Scalar>::type alfa) {
        Container result(a.begin(),a.end());
        std::for_each(result.begin(),result.end(),[&](typename Container::value_type &x){x %= (typename Container::value_type) alfa;});
        return result;
    }

    ///////////////////////////////////////////
    //         NUMERICAL ATTRIBUTION         //
    ///////////////////////////////////////////

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type&
    addition_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            std::transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::plus<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type&
    subtraction_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            std::transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::minus<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type&
    multiplication_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            std::transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::multiplies<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type&
    division_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            std::transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::divides<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && utl::is_container_of_scalar<Container2>::value,Container>::type&
    module_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            std::transform(a.begin(), a.end(), b.begin(),
                      a.begin(), std::modulus<typename Container::value_type>());
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    ///////////////////////////////////////////
    //     NUMERICAL ATTRIBUTION (SCALAR)    //
    ///////////////////////////////////////////

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    addition_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[&](typename Container::value_type &x){x += alfa;});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    subtraction_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[&](typename Container::value_type &x){x -= alfa;});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    multiplication_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[&](typename Container::value_type &x){x *= alfa;});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    division_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[&](typename Container::value_type &x){x /= alfa;});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    module_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[&](typename Container::value_type &x){x %= alfa;});
        return a;
    }

    ////////////////////////////////////////
    //     N-DIMENSIONAL CONTAINERS       //
    ////////////////////////////////////////

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type
    addition(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            for (int i = 0; i < a.size(); ++i) {
                result.push_back(utl::addition(a[i],b[i]));
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type
    subtraction(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            for (int i = 0; i < a.size(); ++i) {
                result.push_back(utl::subtraction(a[i],b[i]));
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type
    multiplication(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            for (int i = 0; i < a.size(); ++i) {
                result.push_back(utl::multiplication(a[i],b[i]));
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type
    division(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            for (int i = 0; i < a.size(); ++i) {
                result.push_back(utl::division(a[i],b[i]));
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type
    module(Container & a, Container2 & b) {
        Container result;
        if (a.size() == b.size()){
            result.reserve(a.size());
            for (int i = 0; i < a.size(); ++i) {
                result.push_back(utl::module(a[i],b[i]));
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return result;
    }

    ////////////////////////////////////////
    //  2-DIMENSIONAL CONTAINERS (SCALAR) //
    ////////////////////////////////////////

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    addition(Container & a, Scalar alfa) {
        Container result(a.begin(),a.end());
        std::for_each(result.begin(),result.end(),[alfa](typename Container::value_type &x){utl::addition(x,alfa);});
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    subtraction(Container & a, Scalar alfa) {
        Container result(a.begin(),a.end());
        std::for_each(result.begin(),result.end(),[alfa](typename Container::value_type &x){utl::subtraction(x,alfa);});
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    multiplication(Container & a, Scalar alfa) {
        Container result(a.begin(),a.end());
        std::for_each(result.begin(),result.end(),[alfa](typename Container::value_type &x){utl::multiplication(x,alfa);});
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    division(Container & a, Scalar alfa) {
        Container result(a.begin(),a.end());
        std::for_each(result.begin(),result.end(),[alfa](typename Container::value_type &x){utl::division(x,alfa);});
        return result;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type
    module(Container & a, Scalar alfa) {
        Container result(a.begin(),a.end());
        std::for_each(result.begin(),result.end(),[alfa](typename Container::value_type &x){utl::module(x,alfa);});
        return result;
    }

    ////////////////////////////////////////
    //      2-D NUMERICAL ATTRIBUTION     //
    ////////////////////////////////////////

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type&
    addition_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            for (int i = 0; i < a.size(); ++i) {
                utl::addition_in_place(a[i],b[i]);
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type&
    subtraction_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            for (int i = 0; i < a.size(); ++i) {
                utl::subtraction_in_place(a[i],b[i]);
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type&
    multiplication_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            for (int i = 0; i < a.size(); ++i) {
                utl::multiplication_in_place(a[i],b[i]);
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type&
    division_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            for (int i = 0; i < a.size(); ++i) {
                utl::division_in_place(a[i],b[i]);
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    template<class Container, class Container2>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && utl::is_container_of_container_of_scalar<Container2>::value,Container>::type&
    module_in_place(Container & a, Container2 & b) {
        if (a.size() == b.size()){
            for (int i = 0; i < a.size(); ++i) {
                utl::module_in_place(a[i],b[i]);
            }
        } else {
            throw std::logic_error("The containers should have the same size");
        }
        return a;
    }

    ////////////////////////////////////////
    // 2-D NUMERICAL ATTRIBUTION (SCALAR) //
    ////////////////////////////////////////

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    addition_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[alfa](typename Container::value_type &x){utl::addition_in_place(x,alfa);});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    subtraction_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[alfa](typename Container::value_type &x){utl::subtraction_in_place(x,alfa);});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    multiplication_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[alfa](typename Container::value_type &x){utl::multiplication_in_place(x,alfa);});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    division_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[alfa](typename Container::value_type &x){utl::division_in_place(x,alfa);});
        return a;
    }

    template<class Container, class Scalar>
    typename std::enable_if<utl::is_container_of_container_of_scalar<Container>::value && std::is_scalar<Scalar>::value,Container>::type&
    module_in_place(Container & a, Scalar alfa) {
        std::for_each(a.begin(),a.end(),[alfa](typename Container::value_type &x){utl::module_in_place(x,alfa);});
        return a;
    }

}

#endif //WPP_CONTAINER_OVERLOADS_H
