//
// Created by Alan de Freitas on 13/09/17.
//

#ifndef TEXT_TABLE_CENTERED_H
#define TEXT_TABLE_CENTERED_H

#include <string>
#include <iostream>
#include <iomanip>

template<typename charT, typename traits = std::char_traits<charT> >
class center_helper {
        std::basic_string<charT, traits> str_;
    public:
        center_helper(std::basic_string<charT, traits> str) : str_(str) {}
        template<typename a, typename b>
        friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);
};

template<typename charT, typename traits = std::char_traits<charT> >
inline center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
    return center_helper<charT, traits>(str);
}

// redeclare for std::string directly so we can support anything that implicitly converts to std::string
inline center_helper<std::string::value_type, std::string::traits_type> centered(const std::string& str) {
    return center_helper<std::string::value_type, std::string::traits_type>(str);
}

template<typename charT, typename traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& s, const center_helper<charT, traits>& c) {
    std::streamsize w = s.width();
    if (w > c.str_.length()) {
        std::streamsize right = (w - c.str_.length()) / 2;
        std::streamsize left = (w - c.str_.length()) - right;
        s.width(left);
        s << "";
        s.width(c.str_.length());
        s << c.str_;
        s.width(right);
        s << "";
    } else {
        s << c.str_;
    }
    return s;
}


#endif //TEXT_TABLE_CENTERED_H
