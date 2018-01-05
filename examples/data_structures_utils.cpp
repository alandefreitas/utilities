#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <utility>
#include <iostream>
#include <cstdlib>

#include "utils.h"

using namespace std;
using namespace utl;

int get_even_random_number() {
    int i = rand();
    return (i % 2 == 0) ? i : -1;
}

optional<int> get_even_random_number1() {
    int i = rand();
    return (i % 2 == 0) ? i : optional<int>{};
}

optional<int> get_even_random_number2() {
    int i = rand();
    return optional<int>{i % 2 == 0, i};
}

optional<int> get_even_random_number3() {
int i = rand();
    return boost::make_optional(i % 2 == 0, i);
}

struct string_to_int_translator {
    typedef string internal_type;
    typedef int external_type;

    optional<int> get_value(const string &s) {
        char *c;
        long l = strtol(s.c_str(), &c, 10);
        return make_optional(c != s.c_str(), static_cast<int>(l));
    }
};

struct output_example : public static_visitor<>
{
    void operator()(double d) const { cout << d << '\n'; }
    void operator()(char c) const { cout << c << '\n'; }
    void operator()(string s) const { cout << s << '\n'; }
};

struct output_example2 : public static_visitor<>
{
    template <typename T>
    void operator()(T t) const { cout << t << '\n'; }
};

struct print
{
    template <typename T>
    void operator()(const T &t) const
    {
        cout << boolalpha << t << '\n';
    }
};

int main()
{
    cout << on_yellow << bold << underline << "JSON Modern C++"
              << reset << endl;
    {
        // create an empty structure (null)
        json j;

        cout << bold << underline << "JSON from initializer list" << reset << endl;

        j = {
                {"pi",      3.141},
                {"happy",   true},
                {"name",    "Niels"},
                {"nothing", nullptr},
                {"answer",  {
                                    {"everything", 42}
                            }},
                {"list",    {       1, 0, 2}},
                {"object",  {
                                    {"currency",   "USD"},
                                       {"value", 42.99}
                            }}
        };

        j["object"] = {
                {"currency", "USD"},
                {"value",    42.99},
                {"country",  "USA"}
        };

        cout << "j: " << j << endl;

        cout << bold << underline << "JSON from string" << reset << endl;

        j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

        cout << "j: " << j << endl;

        j = R"(
      {
        "happy": true,
        "pi": 3.141
      }
    )"_json;

        cout << "j: " << j << endl;

        j = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

        cout << "j: " << j << endl;

        cout << bold << underline << "JSON to string" << reset << endl;

        string s = j.dump();    // {\"happy\":true,\"pi\":3.141}

        cout << "s: " << s << endl;

        cout << bold << underline << "JSON to prettified string" << reset << endl;

        cout << "j.dump(4): " << j.dump(4) << endl;
    }

    cout << on_yellow << bold << underline << "\"Any\""
              << reset << endl;

    cout << bold << underline << "Using any" << reset << endl;
    {
        any a = 1;
        cout << "any_cast<int>(a) : " << any_cast<int>(a) << endl;
        a = 3.14;
        cout << "any_cast<double>(a) : " << any_cast<double>(a) << endl;
        a = true;
        cout << "any_cast<bool>(a) : " << any_cast<bool>(a) << endl;
    }

    cout << bold << underline << "Storing a string in any" << reset << endl;
    {
        any a = string{"Boost"};
    }

    cout << bold << underline << "Accessing values with any_cast" << reset << endl;
    {
        any a = 1;
        cout << any_cast<int>(a) << '\n';
        a = 3.14;
        cout << any_cast<double>(a) << '\n';
        a = true;
        cout << boolalpha << any_cast<bool>(a) << '\n';
    }

    cout << bold << underline << "bad_any_cast in case of an error" << reset << endl;
    {
        try
        {
            any a = 1;
            cout << any_cast<float>(a) << '\n';
        }
        catch (bad_any_cast &e)
        {
            cerr << e.what() << '\n';
        }
    }

    cout << bold << underline << "Checking type of currently stored value" << reset << endl;
    {
        any a = 1;
        if (!a.empty())
        {
            const type_info &ti = a.type();
            cout << ti.name() << '\n';
        }
    }

    cout << bold << underline << "Accessing values through a pointer" << reset << endl;
    {
        any a = 1;
        int *i = utl::any_cast<int>(&a);
        cout << *i << '\n';
    }


    cout << on_yellow << bold << underline << "Optional data"
              << reset << endl;
    cout << bold << underline << "Special values to denote optional return values" << reset << endl;
    {
        srand(static_cast<unsigned int>(time(0)));
        int i = get_even_random_number();
        if (i != -1) {
            cout << sqrt(static_cast<float>(i)) << '\n';
        } else {
            cout << "No square root" << '\n';
        }
    }

    cout << bold << underline << "Optional return values with optional" << reset << endl;
    {
        srand(static_cast<unsigned int>(time(0)));
        optional<int> i = get_even_random_number1();
        if (i) {
            cout << sqrt(static_cast<float>(*i)) << '\n';
        } else {
            cout << "No square root" << '\n';
        }
    }

    cout << bold << underline << "Other useful member functions of optional" << reset << endl;
    {
        srand(static_cast<unsigned int>(time(0)));
        optional<int> i = get_even_random_number2();
        if (i.is_initialized()) {
            cout << sqrt(static_cast<float>(i.get())) << '\n';
        }
    }

    cout << bold << underline << "Various helper functions of Boost.Optional" << reset << endl;
    {
        srand(static_cast<unsigned int>(time(0)));
        optional<int> i = get_even_random_number3();
        double d = get_optional_value_or(i, 0.0);
        cout << sqrt(d) << '\n';
    }

    cout << on_yellow << bold << underline << "Property Tree" << reset << endl;
    cout << bold << underline << "Accessing data in ptree" << reset << endl;
    {
        ptree pt;
        pt.put("C:.Windows.System", "20 files");

        ptree &c = pt.get_child("C:");
        ptree &windows = c.get_child("Windows");
        ptree &system = windows.get_child("System");
        cout << system.get_value<string>() << '\n';
    }

    cout << bold << underline << "Accessing data in basic_ptree<string, int>" << reset << endl;
    {
        using ptree = property_tree::basic_ptree<string, int>;
        ptree pt;
        pt.put(ptree::path_type{"C:\\Windows\\System", '\\'}, 20);
        pt.put(ptree::path_type{"C:\\Windows\\Cursors", '\\'}, 50);

        ptree &windows = pt.get_child(ptree::path_type{"C:\\Windows", '\\'});
        int files = 0;
        for (const pair<string, ptree> &p : windows) {
            files += p.second.get_value<int>();
        }
        cout << files << '\n';
    }

    cout << bold << underline << "Accessing data with a translator" << reset << endl;
    {
        typedef property_tree::iptree ptree;
        ptree pt;
        pt.put(ptree::path_type{"C:\\Windows\\System", '\\'}, "20 files");
        pt.put(ptree::path_type{"C:\\Windows\\Cursors", '\\'}, "50 files");

        string_to_int_translator tr;
        int files =
                pt.get<int>(ptree::path_type{"c:\\windows\\system", '\\'}, tr) +
                pt.get<int>(ptree::path_type{"c:\\windows\\cursors", '\\'}, tr);
        cout << files << '\n';
    }

    cout << bold << underline << "Various member functions of property_tree::ptree" << reset << endl;
    {
        ptree pt;
        pt.put("C:.Windows.System", "20 files");

        optional<string> c = pt.get_optional<string>("C:");
        cout << boolalpha << c.is_initialized() << '\n';

        pt.put_child("D:.Program Files", ptree{"50 files"});
        pt.add_child("D:.Program Files", ptree{"60 files"});

        ptree d = pt.get_child("D:");
        for (const pair<string, ptree> &p : d) {
            cout << p.second.get_value<string>() << '\n';
        }

        optional<ptree &> e = pt.get_child_optional("E:");
        cout << e.is_initialized() << '\n';
    }

    cout << bold << underline << "Serializing a property_tree::ptree in the JSON format" << reset << endl;
    {
        ptree pt;
        pt.put("C:.Windows.System", "20 files");
        pt.put("C:.Windows.Cursors", "50 files");

        property_tree::json_parser::write_json("file.json", pt);

        ptree pt2;
        property_tree::json_parser::read_json("file.json", pt2);

        cout << boolalpha << (pt == pt2) << '\n';
    }

    cout << on_yellow << bold << underline << "Tribool"
              << reset << endl;
    cout << bold << underline << "Three states of logic::tribool" << reset << endl;
    {
        tribool b;
        cout << boolalpha << b << '\n';

        b = true;
        b = false;
        b = indeterminate;
        if (b)
            ;
        else if (!b)
            ;
        else
            cout << "indeterminate\n";
    }

    cout << bold << underline << "Logical operators with logic::tribool" << reset << endl;
    {
        cout.setf(ios::boolalpha);

        tribool b1 = true;
        cout << (b1 || indeterminate) << '\n';
        cout << (b1 && indeterminate) << '\n';

        tribool b2 = false;
        cout << (b2 || indeterminate) << '\n';
        cout << (b2 && indeterminate) << '\n';

        tribool b3 = indeterminate;
        cout << (b3 || b3) << '\n';
        cout << (b3 && b3) << '\n';
    }

    cout << on_yellow << bold << underline << "Variant"
              << reset << endl;
    cout << bold << underline << "Using variant" << reset << endl;
    {
        variant<double, char, string> v;
        v = 3.14;
        v = 'A';
        v = "Boost";
    }

    cout << bold << underline << "Accessing values in variant with get()" << reset << endl;
    {
        variant<double, char, string> v;
        v = 3.14;
        cout << getter::get<double>(v) << '\n';
        v = 'A';
        cout << getter::get<char>(v) << '\n';
        v = "Boost";
        cout << getter::get<string>(v) << '\n';
    }

    cout << bold << underline << "Direct streams of variant on a stream" << reset << endl;
    {
        variant<double, char, string> v;
        v = 3.14;
        cout << v << '\n';
        v = 'A';
        cout << v << '\n';
        v = "Boost";
        cout << v << '\n';
    }

    cout << bold << underline << "Using a visitor for variant" << reset << endl;
    {
        variant<double, char, string> v;
        v = 3.14;
        apply_visitor(output_example{}, v);
        v = 'A';
        apply_visitor(output_example{}, v);
        v = "Boost";
        apply_visitor(output_example{}, v);
    }

    cout << bold << underline << "Using a visitor with a function template for variant" << reset << endl;
    {
        variant<double, char, string> v;
        v = 3.14;
        apply_visitor(output_example2{}, v);
        v = 'A';
        apply_visitor(output_example2{}, v);
        v = "Boost";
        apply_visitor(output_example2{}, v);
    }

    cout << bold << on_yellow << "Generic Fusion Tuples" << reset << endl;
    cout << bold << underline << "Processing Fusion tuples" << reset << endl;
    {
        typedef fusion::tuple<int, string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        cout << "get<0>(t): " << fusion::get<0>(t) << '\n';
        cout << "get<1>(t): " << fusion::get<1>(t) << '\n';
        cout << "boolalpha << get<2>(t): " << boolalpha << fusion::get<2>(t) << '\n';
        cout << "get<3>(t): " << fusion::get<3>(t) << '\n';
    }

    cout << bold << underline << "Iterating over a tuple with fusion::for_each()"
              << reset << endl;
    {
        typedef fusion::tuple<int, string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        fusion::for_each(t, print{});
    }

    cout << bold << underline << "Filtering a Fusion container with fusion::filter_view" << reset << endl;
    {
        typedef fusion::tuple<int, string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        fusion::filter_view<tuple_type, is_integral<mpl::arg<1>>> v{t};
        fusion::for_each(v, print{});
    }

    cout << bold << underline << "Accessing elements in Fusion containers with iterators"
              << reset << endl;
    {
        typedef fusion::tuple<int, string, bool, double> tuple_type;
        tuple_type t{10, "Boost", true, 3.14};
        auto it = begin(t);
        cout << *it << '\n';
        auto it2 = advance<mpl::int_<2>>(it);
        cout << boolalpha << *it2 << '\n';
    }

    cout << bold << underline << "A heterogeneous vector with fusion::vector"
              << reset << endl;
    {
        typedef fusion::vector<int, string, bool, double> vector_type;
        vector_type v{10, "Boost", true, 3.14};
        cout << fusion::at<mpl::int_<0>>(v) << '\n';

        auto v2 = fusion::push_back(v, 'X');
        cout << size(v) << '\n';
        cout << size(v2) << '\n';
        cout << back(v2) << '\n';
    }

    cout << bold << underline << "A heterogeneous map with fusion::map" << reset << endl;
    {
        auto m = fusion::make_map<int, string, bool, double>("Boost", 10, 3.14, true);
        if (fusion::has_key<string>(m)) {
            cout << fusion::at_key<string>(m) << '\n';
        }
        auto m2 = fusion::erase_key<string>(m);
        auto m3 = fusion::push_back(m2, fusion::make_pair<float>('X'));
        cout << boolalpha << fusion::has_key<string>(m3) << '\n';
    }

    return 0;
}
