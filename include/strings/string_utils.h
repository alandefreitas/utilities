//
// Created by Alan de Freitas on 27/09/16.
//

#ifndef WPP_STRING_UTILS_H
#define WPP_STRING_UTILS_H

// External
#include <boost/algorithm/string/regex.hpp>

#include <boost/tokenizer.hpp>

#include <boost/algorithm/string.hpp>

#include <boost/format.hpp>

// Internal
#include "php-like.h"
#include "safe_getline.h"

namespace utl {
    // string algorithms
    using boost::algorithm::trim_left;
    using boost::algorithm::trim_left_if;
    using boost::algorithm::trim_left_copy;
    using boost::algorithm::trim_left_copy_if;
    using boost::algorithm::trim_right;
    using boost::algorithm::trim_right_if;
    using boost::algorithm::trim_right_copy;
    using boost::algorithm::trim_right_copy_if;
    using boost::algorithm::trim;
    using boost::algorithm::trim_if;
    using boost::algorithm::trim_copy;
    using boost::algorithm::trim_copy_if;
    using boost::algorithm::to_lower;
    using boost::algorithm::to_lower_copy;
    using boost::algorithm::to_upper;
    using boost::algorithm::to_upper_copy;
    using boost::algorithm::starts_with;
    using boost::algorithm::istarts_with;
    using boost::algorithm::ends_with;
    using boost::algorithm::iends_with;
    using boost::algorithm::contains;
    using boost::algorithm::icontains;
    using boost::algorithm::equals;
    using boost::algorithm::iequals;
    using boost::algorithm::all;
    // ::range already has it
    // using boost::algorithm::lexicographical_compare;
    using boost::algorithm::ilexicographical_compare;
    // ::range already has it
    // using boost::algorithm::find;
    using boost::algorithm::find_first;
    using boost::algorithm::ifind_first;
    using boost::algorithm::find_last;
    using boost::algorithm::ifind_last;
    using boost::algorithm::find_nth;
    using boost::algorithm::ifind_nth;
    using boost::algorithm::find_head;
    using boost::algorithm::find_tail;
    using boost::algorithm::find_token;
    using boost::algorithm::find_all;
    using boost::algorithm::ifind_all;
    using boost::algorithm::split;
    using boost::algorithm::join;
    using boost::algorithm::join_if;
    using boost::algorithm::replace_range_copy;
    using boost::algorithm::replace_range;
    using boost::algorithm::replace_first_copy;
    using boost::algorithm::replace_first;
    using boost::algorithm::ireplace_first_copy;
    using boost::algorithm::ireplace_first;
    using boost::algorithm::replace_last_copy;
    using boost::algorithm::replace_last;
    using boost::algorithm::ireplace_last_copy;
    using boost::algorithm::ireplace_last;
    using boost::algorithm::replace_nth_copy;
    using boost::algorithm::replace_nth;
    using boost::algorithm::ireplace_nth_copy;
    using boost::algorithm::ireplace_nth;
    using boost::algorithm::replace_all_copy;
    using boost::algorithm::replace_all;
    using boost::algorithm::ireplace_all_copy;
    using boost::algorithm::ireplace_all;
    using boost::algorithm::replace_head_copy;
    using boost::algorithm::replace_head;
    using boost::algorithm::replace_tail_copy;
    using boost::algorithm::replace_tail;
    using boost::algorithm::erase_range_copy;
    using boost::algorithm::erase_range;
    using boost::algorithm::erase_first_copy;
    using boost::algorithm::erase_first;
    using boost::algorithm::ierase_first_copy;
    using boost::algorithm::ierase_first;
    using boost::algorithm::erase_last_copy;
    using boost::algorithm::erase_last;
    using boost::algorithm::ierase_last_copy;
    using boost::algorithm::ierase_last;
    using boost::algorithm::erase_nth_copy;
    using boost::algorithm::erase_nth;
    using boost::algorithm::ierase_nth_copy;
    using boost::algorithm::ierase_nth;
    using boost::algorithm::erase_all_copy;
    using boost::algorithm::erase_all;
    using boost::algorithm::ierase_all_copy;
    using boost::algorithm::ierase_all;
    using boost::algorithm::erase_head_copy;
    using boost::algorithm::erase_head;
    using boost::algorithm::erase_tail_copy;
    using boost::algorithm::erase_tail;
    using boost::algorithm::is_classified;
    using boost::algorithm::is_space;
    using boost::algorithm::is_alnum;
    using boost::algorithm::is_alpha;
    using boost::algorithm::is_cntrl;
    using boost::algorithm::is_digit;
    using boost::algorithm::is_graph;
    using boost::algorithm::is_lower;
    using boost::algorithm::is_upper;
    using boost::algorithm::is_print;
    using boost::algorithm::is_punct;
    using boost::algorithm::is_xdigit;
    using boost::algorithm::is_any_of;
    using boost::algorithm::is_from_range;
    using boost::algorithm::find_iterator;
    using boost::algorithm::make_find_iterator;
    using boost::algorithm::split_iterator;
    using boost::algorithm::make_split_iterator;

    // Format
    using boost::format;
    namespace io = boost::io;

    // Tokenizers
    using boost::char_separator;
    using boost::keep_empty_tokens;
    using boost::tokenizer;
    using boost::offset_separator;

    using string_tokenizer = boost::tokenizer<boost::char_separator<char>>;
    using wstring_tokenizer = boost::tokenizer<boost::char_separator<wchar_t>,std::wstring::const_iterator, std::wstring>;
    using csv_tokenizer = boost::tokenizer<boost::escaped_list_separator<char>>;
    using offset_tokenizer = boost::tokenizer<boost::offset_separator>;
}

#endif //WPP_STRING_UTILS_H
