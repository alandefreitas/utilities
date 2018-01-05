//
// TEXT_TABLE can read csv now!
//



#ifndef WPP_FILE_UTILS_H
#define WPP_FILE_UTILS_H

#include <string>
#include <stdio.h>

#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>
#include "string_utils.h"


namespace utils {
    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<C<T>>& read_csv_to_double(string filename, C<C<T>> &r, char token = ';'){
        ifstream fin(filename);
        string line;
        while (safeGetline(fin, line)){
            stringstream lineStream(line);
            string cell;
            r.push_back(vector<double>(0));
            while(safeGetline(lineStream,cell,token))
            {
                r.back().push_back(stod(cell));
            }
        }
        return r;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    C<C<T>> read_csv_to_str(string filename, char token = ';'){
        ifstream fin(filename);
        vector<vector<string>> r;
        string line;
        while (safeGetline(fin, line)){
            stringstream lineStream(line);
            string cell;
            r.push_back(vector<string>(0));
            while(safeGetline(lineStream,cell,token))
            {
                r.front().push_back(cell);
            }
        }
        fin.close();
        return r;
    }

    template<template<class B, class All = std::allocator<B> > class C, class T>
    void save_csv(string filename, C<C<T>> m, char delimiter = ';'){
        ofstream fout(filename);
        for_each(m.begin(),m.end(),[&](C<T> &x){
            std::for_each(x.begin(),prev(x.end()),[&](T &x){
                fout << x << delimiter;
            });
            fout << *prev(x.end()) << endl;
        });
        fout.close();
    }
}

#endif //WPP_FILE_UTILS_H
