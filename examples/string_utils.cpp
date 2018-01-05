#include <string>
#include <iostream>
#include <locale>
#include <vector>

#include "utils.h"

using namespace std;
using namespace utl;

struct animal
{
    string name;
    int legs;
};

ostream &operator<<(ostream &os, const animal &a)
{
    return os << a.name << ',' << a.legs;
}

int main()
{
    cout << bold << on_yellow << "String utilities" << reset << endl;

    cout << bold << underline << "Case" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        cout << s << '\n';
        cout << to_upper_copy(s) << '\n';
        cout << to_lower_copy(s) << '\n';
        cout << s << '\n';
        to_lower(s);
        cout << s << '\n';
        to_upper(s);
        cout << s << '\n';
    }

    cout << bold << underline << "Erase substrings" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        cout << erase_first_copy(s, "s") << '\n';
        cout << erase_nth_copy(s, "s", 0) << '\n';
        cout << erase_last_copy(s, "s") << '\n';
        cout << erase_all_copy(s, "s") << '\n';
        cout << erase_head_copy(s, 5) << '\n';
        cout << erase_tail_copy(s, 9) << '\n';
    }

    cout << bold << underline << "Iterate substrings" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        view::iterator_range<string::iterator> r = find_first(s, "C++");
        cout << "substring: " << r << '\n';
        r = find_first(s, "xyz");
        cout << "substring: " << r << '\n';
    }

    cout << bold << underline << "Join strings" << reset << endl;
    {
        vector<string> v{"Boost", "C++", "Libraries"};
        cout << join(v, " ") << '\n';
    }

    cout << bold << underline << "Replace substrings" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        cout << replace_first_copy(s, "+", "-") << '\n';
        cout << replace_nth_copy(s, "+", 0, "-") << '\n';
        cout << replace_last_copy(s, "+", "-") << '\n';
        cout << replace_all_copy(s, "+", "-") << '\n';
        cout << replace_head_copy(s, 5, "BOOST") << '\n';
        cout << replace_tail_copy(s, 9, "LIBRARIES") << '\n';
    }

    cout << bold << underline << "Trim substrings" << reset << endl;
    {
        string s = "\t Boost C++ Libraries \t";
        cout << "_" << trim_left_copy(s) << "_\n";
        cout << "_" << trim_right_copy(s) << "_\n";
        cout << "_" << trim_copy(s) << "_\n";
    }

    cout << bold << underline << "Trim substrings on special chars" << reset << endl;
    {
        string s = "--Boost C++ Libraries--";
        cout << trim_left_copy_if(s, is_any_of("-")) << '\n';
        cout << trim_right_copy_if(s, is_any_of("-")) << '\n';
        cout << trim_copy_if(s, is_any_of("-")) << '\n';
    }

    cout << bold << underline << "Trim substrings on conditions" << reset << endl;
    {
        string s = "123456789Boost C++ Libraries123456789";
        cout << trim_left_copy_if(s, is_digit()) << '\n';
        cout << trim_right_copy_if(s, is_digit()) << '\n';
        cout << trim_copy_if(s, is_digit()) << '\n';
    }

    cout << bold << underline << "Test substrings" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        cout.setf(ios::boolalpha);
        cout << starts_with(s, "Boost") << '\n';
        cout << ends_with(s, "Libraries") << '\n';
        cout << contains(s, "C++") << '\n';
        cout << lexicographical_compare(s, "Boost") << '\n';
    }

    cout << bold << underline << "Split strings" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        vector<string> v;
        split(v, s, is_space());
        cout << v.size() << '\n';
    }

    cout << bold << on_yellow << "Tokenizing strings" << reset << endl;
    cout << bold << underline << "Iterate string tokens" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        string_tokenizer tok{s};
        for (string_tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) {
            cout << *it << '\n';
        }
    }

    cout << bold << underline << "Iterate string token with special separators" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        char_separator<char> sep{" "};
        string_tokenizer tok{s, sep};
        for (const auto &t : tok) {
            cout << t << '\n';
        }
    }

    cout << bold << underline << "Iterate string token with special separators" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        char_separator<char> sep{" ", "+"};
        string_tokenizer tok{s, sep};
        for (const auto &t : tok) {
            cout << t << '\n';
        }
    }

    cout << bold << underline << "Iterate string keeping tokens" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        char_separator<char> sep{" ", "+", keep_empty_tokens};
        string_tokenizer tok{s, sep};
        for (const auto &t : tok) {
            cout << t << '\n';
        }
    }

    cout << bold << underline << "Iterate wide strings" << reset << endl;
    {
        wstring s = L"Boost C++ Libraries";
        char_separator<wchar_t> sep{L" "};
        wstring_tokenizer tok{s, sep};
        for (const auto &t : tok) {
            wcout << t << '\n';
        }
    }

    cout << bold << underline << "Iterate separators" << reset << endl;
    {
        string s = "Boost,\"C++ Libraries\"";
        csv_tokenizer tok{s};
        for (const auto &t : tok) {
            cout << t << '\n';
        }
    }

    cout << bold << underline << "Iterate string offsetting separators" << reset << endl;
    {
        typedef tokenizer<offset_separator> my_tokenizer;
        string s = "Boost_C++_Libraries";
        int offsets[] = {5, 5, 9};
        offset_separator sep{offsets, offsets + 3};
        my_tokenizer tok{s, sep};
        for (const auto &t : tok) {
            cout << t << '\n';
        }
    }


    cout << bold << underline << "Iterating over partial expressions in a string with string_tokenizer" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        string_tokenizer tok{s};
        for (string_tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
            cout << *it << '\n';
    }

    cout << bold << underline << "Initializing char_separator to adapt the iteration" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        char_separator<char> sep{" "};
        string_tokenizer tok{s, sep};
        for (const auto &t : tok)
            cout << t << '\n';
    }

    cout << bold << underline << "Simulating the default behavior with char_separator" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        char_separator<char> sep{" ", "+"};
        string_tokenizer tok{s, sep};
        for (const auto &t : tok)
            cout << t << '\n';
    }

    cout << bold << underline << "Initializing char_separator to display empty partial expressions" << reset << endl;
    {
        string s = "Boost C++ Libraries";
        char_separator<char> sep{" ", "+", keep_empty_tokens};
        string_tokenizer tok{s, sep};
        for (const auto &t : tok)
            cout << t << '\n';
    }

    cout << bold << underline << "Boost.Tokenizer with wide strings" << reset << endl;
    {
        wstring s = L"Boost C++ Libraries";
        char_separator<wchar_t> sep{L" "};
        wstring_tokenizer tok{s, sep};
        for (const auto &t : tok)
            wcout << t << '\n';
    }

    cout << bold << underline << "Parsing CSV files with escaped_list_separator" << reset << endl;
    {
        string s = "Boost,\"C++ Libraries\"";
        csv_tokenizer tok{s};
        for (const auto &t : tok)
            cout << t << '\n';
    }

    cout << bold << underline << "Iterating over partial expressions with offset_separator" << reset << endl;
    {
        string s = "Boost_C++_Libraries";
        int offsets[] = {5, 5, 9};
        offset_separator sep{offsets, offsets + 3};
        offset_tokenizer tok{s, sep};
        for (const auto &t : tok)
            cout << t << '\n';
    }

    cout << bold << on_yellow << "Formatted streams" << reset << endl;

    cout << bold << underline << "Formatted streams" << reset << endl;
    {
        cout << format{"%1%.%2%.%3%"} % 12 % 5 % 2014 << '\n';
    }

    cout << bold << underline << "Numbered placeholders" << reset << endl;
    {
        cout << format{"%2%/%1%/%3%"} % 12 % 5 % 2014 << '\n';
    }

    cout << bold << underline << "Using manipulators with io::group()" << reset << endl;
    {
        // uses the manipulator showpos() on the value that will be associated with “%1%”
        cout << format{"%1% %2% %1%"} % io::group(showpos, 1) % 2 << '\n';
    }

    // http://www.boost.org/libs/format/doc/format.html#printf_directives
    cout << bold << underline << "Placeholders with special characters" << reset << endl;
    {
        // the first instance of the placeholder “%1%” is replaced with “%|1$+|”
        cout << format{"%|1$+| %2% %1%"} % 1 % 2 << '\n';
    }

    cout << bold << underline << "io::format_error in case of an error" << reset << endl;
    {
        try
        {
            cout << format{"%|+| %2% %1%"} % 1 % 2 << '\n';
        }
        catch (io::format_error &ex)
        {
            cout << ex.what() << '\n';
        }
    }

    cout << bold << underline << "Placeholders without numbers" << reset << endl;
    {
        cout << format{"%|+| %|| %||"} % 1 % 2 % 1 << '\n';
    }

    cout << bold << underline << "format with the syntax used from printf()" << reset << endl;
    {
        cout << format{"%+d %d %d"} % 1 % 2 % 1 << '\n';
    }

    cout << bold << underline << "format with seemingly invalid placeholders" << reset << endl;
    {
        cout << format{"%+s %s %s"} % 1 % 2 % 1 << '\n';
    }

    cout << bold << underline << "format with user-defined type" << reset << endl;
    {
        animal a{"cat", 4};
        cout << format{"%1%"} % a << '\n';
    }

    return 0;
}
