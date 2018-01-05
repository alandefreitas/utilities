#include <boost/phoenix/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

#include "include/termcolor/termcolor.hpp"

using namespace boost::spirit;

struct print : public boost::static_visitor<>
{
    template <typename T>
    void operator()(T t) const
    {
        std::cout << std::boolalpha << t << ';';
    }
};

typedef boost::variant<int, bool> int_or_bool;

struct int_or_bool_values
{
    int_or_bool first;
    std::vector<int_or_bool> others;
};

// This macro makes it possible to treat int_or_bool_values like a tuple with two values of type int_or_bool and std::vector<int_or_bool>
BOOST_FUSION_ADAPT_STRUCT(
        int_or_bool_values,
        (int_or_bool, first)
                (std::vector<int_or_bool>, others)
)

template <typename Iterator, typename Skipper>
struct my_grammar : qi::grammar<Iterator, int_or_bool_values(), Skipper>
{
    my_grammar() : my_grammar::base_type{values}
    {
        value = qi::int_ | qi::bool_;
        // first component has to be stored in an object of type boost::variant. The values parsed by the second component have to be stored in a container
        values = value >> ',' >> value % ',';
    }

    qi::rule<Iterator, int_or_bool(), Skipper> value;
    qi::rule<Iterator, int_or_bool_values(), Skipper> values;
};

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Using boost::spirit::qi::parse()" << termcolor::reset << std::endl;
    {
        std::cout << "Type a number: 45" << std::endl;
        std::string s = "45";
        //std::getline(std::cin, s);
        auto it = s.begin();
        bool match = qi::parse(it, s.end(), ascii::digit);
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Using boost::spirit::qi::phrase_parse()" << termcolor::reset << std::endl;
    {
        std::string s = "32";
        //std::getline(std::cin, s);
        auto it = s.begin();
        bool match = qi::phrase_parse(it, s.end(), ascii::digit, ascii::space); // skipper
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "phrase_parse() with boost::spirit::qi::skip_flag::dont_postskip" << termcolor::reset << std::endl;
    {
        std::string s = "321";
        //std::getline(std::cin, s);
        auto it = s.begin();
        bool match = qi::phrase_parse(it, s.end(), ascii::digit, ascii::space,
                                      qi::skip_flag::dont_postskip);
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "boost::spirit::qi::phrase_parse() with wide strings" << termcolor::reset << std::endl;
    {
        std::wstring s = L"431";
        //std::getline(std::wcin, s);
        auto it = s.begin();
        bool match = qi::phrase_parse(it, s.end(), ascii::digit, ascii::space,
                                      qi::skip_flag::dont_postskip);
        std::wcout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::wcout << std::wstring{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "A parser for two consecutive digits" << termcolor::reset << std::endl;
    {
        std::string s = "32";
        //std::getline(std::cin, s);
        auto it = s.begin();
        bool match = qi::phrase_parse(it, s.end(), ascii::digit >> ascii::digit, ascii::space);
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Parsing character by character with boost::spirit::qi::lexeme" << termcolor::reset << std::endl;
    {
        std::string s = "43";
        //std::getline(std::cin, s);
        auto it = s.begin();
        // only returns true if the digits have no spaces between them
        bool match = qi::phrase_parse(it, s.end(),
                                      qi::lexeme[ascii::digit >> ascii::digit], ascii::space);
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Boost.Spirit rules similar to regular expressions" << termcolor::reset << std::endl;
    {
        std::string s = "3298";
        //std::getline(std::cin, s);
        auto it = s.begin();
        bool match = qi::phrase_parse(it, s.end(), +ascii::digit, ascii::space);
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Numeric parsers" << termcolor::reset << std::endl;
    {
        std::string s = "+3214";
        //std::getline(std::cin, s);
        auto it = s.begin();
        bool match = qi::phrase_parse(it, s.end(), qi::int_, ascii::space);
        // boost::spirit::qi::float_, boost::spirit::qi::double_, and boost::spirit::qi::bool_
        // boost::spirit::qi::eol
        // boost::spirit::qi::byte_ and boost::spirit::qi::word can be used to read one or two bytes
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Linking actions with parsers" << termcolor::reset << std::endl;
    {
        std::string s = "+321";
        //std::getline(std::cin, s);
        auto it = s.begin();
        bool match = qi::phrase_parse(it, s.end(),
                                      qi::int_[([](int i) { std::cout << i << '\n'; })], ascii::space);
        std::cout << std::boolalpha << match << '\n';
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Boost.Spirit with Boost.Phoenix" << termcolor::reset << std::endl;
    {
        using boost::phoenix::ref;

        std::string s = "3982";
        //std::getline(std::cin, s);
        auto it = s.begin();
        int i;
        bool match = qi::phrase_parse(it, s.end(), qi::int_[ref(i) = qi::_1],
                                      ascii::space);
        std::cout << std::boolalpha << match << '\n';
        if (match) {
            std::cout << i << '\n';
        }
        if (it != s.end()) {
            std::cout << std::string{it, s.end()} << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Storing an int value in an attribute" << termcolor::reset << std::endl;
    {
        std::string s = "5298";
        //std::getline(std::cin, s);
        auto it = s.begin();
        int i;
        if (qi::phrase_parse(it, s.end(), qi::int_, ascii::space, i)) {
            std::cout << i << '\n';
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Storing several int values in an attribute" << termcolor::reset << std::endl;
    {
        std::string s = "321,452,543,321";
        //std::getline(std::cin, s);
        auto it = s.begin();
        std::vector<int> v;
        if (qi::phrase_parse(it, s.end(), qi::int_ % ',', ascii::space, v)) {
            std::ostream_iterator<int> out{std::cout, ";"};
            std::copy(v.begin(), v.end(), out);
        }
        std::cout << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Defining rules with boost::spirit::qi::rule" << termcolor::reset << std::endl;
    {
        std::string s = "321,543,6543,21";
        //std::getline(std::cin, s);
        auto it = s.begin();
        // The only mandatory parameter is the iterator type of the string being parsed
        // The second template parameter is std::vector<int>(), which is the signature of a function that returns a vector of type std::vector<int> and expects no parameter
        // The third template parameter is the type of the skipper used by boost::spirit::qi::phrase_parse().
        qi::rule<std::string::iterator, std::vector<int>(),
                ascii::space_type> values = qi::int_ % ',';
        std::vector<int> v;
        if (qi::phrase_parse(it, s.end(), values, ascii::space, v))
        {
            std::ostream_iterator<int> out{std::cout, ";"};
            std::copy(v.begin(), v.end(), out);
        }
        std::cout << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Nesting Rules" << termcolor::reset << std::endl;
    {
        std::string s = "312,true,3432,false";
        //std::getline(std::cin, s);
        auto it = s.begin();
        qi::rule<std::string::iterator, boost::variant<int, bool>(),
                ascii::space_type> value = qi::int_ | qi::bool_;
        qi::rule<std::string::iterator, std::vector<boost::variant<int, bool>>(),
                ascii::space_type> values = value % ',';
        std::vector<boost::variant<int, bool>> v;
        if (qi::phrase_parse(it, s.end(), values, ascii::space, v))
        {
            for (const auto &elem : v)
                boost::apply_visitor(print{}, elem);
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Parsing" << termcolor::reset << std::endl;
    {
        std::string s = "3214,true,false,3213";
        //std::getline(std::cin, s);
        auto it = s.begin();
        my_grammar<std::string::iterator, ascii::space_type> g;
        int_or_bool_values v;
        if (qi::phrase_parse(it, s.end(), g, ascii::space, v))
        {
            print p;
            boost::apply_visitor(p, v.first);
            for (const auto &elem : v.others)
                boost::apply_visitor(p, elem);
        }
    }



}