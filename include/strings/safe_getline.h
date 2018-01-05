//
// Created by Alan de Freitas on 03/01/18.
//

#ifndef UTILITIES_SAFE_GETLINE_H
#define UTILITIES_SAFE_GETLINE_H

#include <string>
#include <stdio.h>

#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <sstream>
#include <unordered_map>


namespace utl {

    template <class IS = std::istream, class STRING = std::string, class DELIM = char>
    bool safe_getline(IS& is, STRING& t, DELIM delim = ';')
    {
        t.clear();
        // The characters in the stream are read one-by-one using a std::streambuf.
        // That is faster than reading them one-by-one using the std::istream.
        // Code that uses streambuf this way must be guarded by a sentry object.
        // The sentry object performs various tasks,
        // such as thread synchronization and updating the stream state.
        std::istream::sentry se(is, true);
        std::streambuf* sb = is.rdbuf();

        while (true) {
            int c = sb->sbumpc();
            if (c == '\n'){
                return !t.empty();
            } else if (c == '\r'){
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return !t.empty();
            } else if (c == delim){
                if((sb->sgetc() == '\n')||(sb->sgetc() == '\r')){
                    sb->sbumpc();
                }
                return !t.empty();
            } else if (c == EOF){
                // Also handle the case when the last line has no line ending
                if(t.empty())
                    is.setstate(std::ios::eofbit);
                return !t.empty();
            } else {
                t += (char)c;
            }
        }
    }

}


#endif //UTILITIES_SAFE_GETLINE_H
