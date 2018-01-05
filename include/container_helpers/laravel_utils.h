//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef LARAVEL_CONTAINER_UTILS_H
#define LARAVEL_CONTAINER_UTILS_H

#include <stdio.h>
#include <ctype.h>


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

#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace utils {

    template<class T>
    std::vector<T> flatten(std::vector<std::pair<T, std::vector<T>>> &c) {
        std::vector<T> flattened;
        for (std::pair<T, std::vector<T>> &&p : c) {
            for (std::vector<T> &item : p.second) {
                flattened.push_back(item);
            }
        }
        return flattened;
    }

    template<class C, class T>
    std::vector<T> flatten(C &c) {
        std::vector<T> flattened;
        for (std::pair<T, std::vector<T>> &&p : c) {
            for (std::vector<T> &item : p.second) {
                flattened.push_back(item);
            }
        }
        return flattened;
    }


    template<class T>
    std::vector<T> flatten(std::vector<std::pair<T, T>> &c) {
        std::vector<T> flattened;
        for (std::pair<T, std::vector<T>> &&p : c) {
            flattened.push_back(p.second);
        }
        return flattened;
    }

}

#endif //LARAVEL_CONTAINER_UTILS_H
