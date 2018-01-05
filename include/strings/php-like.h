//
// Created by Alan de Freitas on 03/01/18.
//

#ifndef UTILITIES_PHP_LIKE_STRING_UTILS_H
#define UTILITIES_PHP_LIKE_STRING_UTILS_H

#include <string>
#include <stdio.h>

#include <numeric>
#include <random>
#include <math.h>
#include <functional>
#include <limits>
#include <fstream>
#include <regex>
#include <sstream>
#include <unordered_map>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/tokenizer.hpp>

namespace utl {
    // Determine if a given std::string contains a given substd::string.
    bool contains(std::string const & haystack, std::string needle)
    {
        return haystack.find(needle) != std::string::npos;
    }

    std::string lower(std::string value)
    {
        return boost::algorithm::to_lower_copy(value);
    }

    bool ctype_lower(std::string str){
        for (char &c : str) {
            if (!islower(c)){
                return false;
            }
        }
        return true;
    }

    std::string preg_replace(std::regex pattern, std::string replacement, std::string subject)
    {
        return std::regex_replace(subject,pattern,replacement);
    }

    std::string preg_replace(std::string pattern, std::string replacement, std::string subject)
    {
        return std::regex_replace(subject,std::regex(pattern),replacement);
    }

    std::string preg_replace(const char* pattern, std::string replacement, std::string subject)
    {
        return std::regex_replace(subject,std::regex(std::string(pattern)),replacement);
    }

    std::string preg_replace(std::regex pattern, std::string replacement, std::string subject, int limit)
    {
        if (limit >= 0){
            for (int i = 0; i < limit; ++i) {
                subject = std::regex_replace(subject,pattern,replacement,std::regex_constants::format_first_only);
            }
        }
        return subject;
    }

    std::string preg_replace(std::string pattern, std::string replacement, std::string subject, int limit)
    {
        return utl::preg_replace(std::regex(pattern),replacement,subject,limit);
    }

    std::string preg_replace(const char* pattern, std::string replacement, std::string subject, int limit)
    {
        return utl::preg_replace(std::regex(std::string(pattern)),replacement,subject,limit);
    }

    std::string snake(std::string value, std::string delimiter = "_")
    {
        std::string key = value;

        static std::unordered_map<std::string,std::map<std::string,std::string>> snake_cache;

        if (snake_cache[key].count(delimiter)) {
            return snake_cache[key][delimiter];
        }

        if (!utl::ctype_lower(value)) {
            value = utl::preg_replace("/\\s+/u", "", value);
            value = utl::lower(preg_replace("/(.)(?=[A-Z])/u", "$1" + delimiter, value));
        }

        return snake_cache[key][delimiter] = value;
    }

    inline bool is_double(const std::string & s)
    {
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

        char * p ;
        std::strtod(s.c_str(), &p) ;

        return (*p == 0) ;
    }

    inline bool is_int(const std::string & s)
    {
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

        char * p ;
        std::strtol(s.c_str(), &p, 10) ;

        return (*p == 0) ;
    }


    inline std::vector<std::string> explode(std::string delimiters, std::string input)
    {
        std::vector<std::string> v;
        boost::split(v, input, boost::is_any_of(delimiters));
        return v;
    };

    std::string implode(std::string separator, std::vector<std::string> input)
    {
        return boost::algorithm::join(input,separator);
    };

    template<typename string_type>
    string_type implode(string_type separator, std::vector<string_type> input)
    {
        return boost::algorithm::join(input,separator);
    };


    std::string trim(std::string input, std::string charlist = " \t\n\r\0\x0B")
    {
        return boost::algorithm::trim_copy_if(input,boost::is_any_of(charlist));
    };

    std::string rtrim(std::string input, std::string charlist = " \t\n\r\0\x0B")
    {
        return boost::algorithm::trim_right_copy_if(input,boost::is_any_of(charlist));
    };

    std::string ltrim(std::string input, std::string charlist = " \t\n\r\0\x0B")
    {
        return boost::algorithm::trim_left_copy_if(input, boost::is_any_of(charlist));
    };

    std::string strtolower(std::string s){
        return boost::algorithm::to_lower_copy(s);
    }

    size_t strpos(std::string haystack, std::string needle){
        return haystack.find(needle);
    }

    std::vector<std::string> preg_split(std::regex r, std::string s, bool PREG_SPLIT_NO_EMPTY = false, bool DELIM_CAPTURE = false)
    {
        std::vector<std::string> splits;
        std::smatch m;

        while (std::regex_search(s, m, r))
        {
            int split_on = m.position();
            if (!PREG_SPLIT_NO_EMPTY || 0 != split_on){
                splits.push_back(s.substr(0, split_on));
            }
            s = s.substr(split_on + m.length());
            if (DELIM_CAPTURE){
                for (int i = 1; i < m.size(); ++i) {
                    splits.push_back(m[i]);
                }
            }
        }

        if(!s.empty()) {
            splits.push_back(s); // and there may be one last token at the end
        }

        return splits;
    }

    std::vector<std::string> preg_split(const char* r, std::string s, bool PREG_SPLIT_NO_EMPTY = false, bool DELIM_CAPTURE = false){
        return preg_split(std::regex(std::string(r)),s,PREG_SPLIT_NO_EMPTY,DELIM_CAPTURE);
    }

    std::vector<std::string> preg_split(std::string r, std::string s, bool PREG_SPLIT_NO_EMPTY = false, bool DELIM_CAPTURE = false){
        return preg_split(std::regex(r),s,PREG_SPLIT_NO_EMPTY,DELIM_CAPTURE);
    }




    std::string str_to_lower(std::string str){
        return boost::algorithm::to_lower_copy(str);
    }

    std::string str_replace(std::string search, std::string replace, std::string subject){
        return boost::algorithm::replace_all_copy(subject, search, replace);
    }

    std::string str_replace(std::vector<std::string> search, std::string replace, std::string subject){
        std::string r = subject;
        for (std::string &s : search) {
            boost::algorithm::replace_all(r, s, replace);
        }
        return r;
    }

    std::string ucfirst(std::string str){
        if (str.empty()){
            return str;
        } else if (!islower(str[0])){
            std::string first = boost::algorithm::to_lower_copy(std::string(1,str[0]));
            return first + std::string(str.substr(1));
        } else {
            return str;
        }
    }

    std::string filter_var_int(std::string variable) {
        std::string filtered;
        // copy only numbers, +, and -:
        auto it = std::copy_if (variable.begin(), variable.end(), std::back_inserter(filtered), [](char c){
            return std::regex_match(std::string({c,'\0'}),std::regex("[\\+\\-0-9]"));
        });
        return filtered;
    }


}


#endif //UTILITIES_PHP_LIKE_STRING_UTILS_H
