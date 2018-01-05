#include <vector>
#include <set>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>
#include <array>
#include <deque>
#include <map>
#include <string>
#include <utility>
#include <iterator>
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>

#include "utils.h"

using namespace std;
using namespace utl;

#include "container_helpers_utils.h"

int main(int argc, const char *argv[])
{
    cout << bold << on_yellow << "Container numeric overloads" << reset << endl;

    cout << bold << underline << "Operating on a container" << reset << endl;
    {
        vector<double> x1 = {3.4,2.5,2.6,4.6,3.5};
        vector<double> x2 = {2.3,3.2,1.8,3.6,2.5};
        vector<double> x3 = x1 + x2;
        vector<double> x4 = x3 + 10.0;
        vector<double> x5 = x4 * x2;
        vector<double> x6 = x5 / x1;
        cout << x6 << endl;
    }

    cout << bold << underline << "Operating on a container with scalars" << reset << endl;
    {
        vector<double> x1 = {3.4,2.5,2.6,4.6,3.5};
        double x2 = 20.0;
        vector<double> x3 = x1 * x2;
        cout << x3 << endl;
    }

    cout << bold << underline << "Numerical attribution" << reset << endl;
    {
        vector<double> x1 = {3.4,2.5,2.6,4.6,3.5};
        x1 += 20.0;
        vector<double> x2 = {2.3,3.2,1.8,3.6,2.5};
        x1 *= x2;
        cout << x1 << endl;
    }


    cout << bold << underline << "2D operations" << reset << endl;
    {
        vector<vector<double>> x1 = {{3.4,2.5,2.6,4.6,3.5},{2.3,3.2,1.8,3.6,2.5}};
        x1 += 20.0;
        vector<vector<double>> x2 = {{3.4,2.5,2.6,4.6,3.5},{2.3,3.2,1.8,3.6,2.5}};
        x1 += x2;
        x1 *= x2;
        cout << x1 << endl;
    }

    cout << bold << on_yellow << "Automatic Relational Operators" << reset << endl;

    cout << bold << underline << "Greater-than operator with less_than_comparable"
              << reset << endl;
    {
        comparable_animal a1{"cat", 4};
        comparable_animal a2{"spider", 8};
        cout << boolalpha << "(a2 > a1): " << (a2 > a1) << '\n';
    }

    cout << bold << on_yellow << "Serialization" << reset << endl;

    cout << on_yellow << bold << underline << "Archive"
              << reset << endl;

    cout << bold << underline << "Using text_oarchive"
              << reset << endl;
    {
        text_oarchive oa{cout};
        int i = 1;
        oa << i;
    }

    cout << bold << underline << "Using text_iarchive" << reset
              << endl;
    {
        auto save = []() -> void {
            ofstream file{"archive.txt"};
            text_oarchive oa{file};
            int i = 1;
            oa << i;
        };

        auto load = []() -> void {
            ifstream file{"archive.txt"};
            text_iarchive ia{file};
            int i = 0;
            ia >> i;
            cout << "i: " << i << '\n';
        };

        save();
        load();
    }

    cout << bold << underline << "Serializing with a stringstream" << reset
              << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            int i = 1;
            oa << i;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            int i = 0;
            ia >> i;
            cout << "i: " << i << '\n';
        };

        save();
        load();
    }

    cout << bold << underline << "Serializing user-defined types with a member function"
              << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            animal a{4};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            animal a;
            ia >> a;
            cout << "a.legs(): " << a.legs() << '\n';
        };

        save();
        load();
    }

    cout << bold << underline << "Serializing with a free-standing function"
              << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            free_standing_animal a{4};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            free_standing_animal a;
            ia >> a;
            cout << "a.legs(): " << a.legs() << '\n';
        };

        save();
        load();
    }

    cout << bold << underline << "Serializing strings" << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            named_animal a{4, "cat"};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            named_animal a;
            ia >> a;
            cout << "a.legs(): " << a.legs() << '\n';
            cout << "a.name(): " << a.name() << '\n';
        };

        save();
        load();
    }

    cout << bold << underline << "Backward compatibility with version numbers"
              << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            compatible_animal a{4, "cat"};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            compatible_animal a;
            ia >> a;
            cout << "a.legs(): " << a.legs() << '\n';
            cout << "a.name(): " << a.name() << '\n';
        };

        save();
        load();
    }

    cout << on_yellow << bold << underline << "Pointers and References"
              << reset << endl;

    cout << bold << underline << "Serializing pointers"
              << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            animal *a = new animal{4};
            oa << a;
            cout << "hex << a: " << hex << a << '\n';
            delete a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            animal *a;
            ia >> a;
            cout << "hex << a: " << hex << a << '\n';
            cout << "dec << a->legs(): " << dec << a->legs() << '\n';
            delete a;
        };

        save();
        load();
    }

    cout << bold << underline << "Serializing smart pointers" << reset
              << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            scoped_ptr<animal> a{new animal{4}};
            oa << a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            scoped_ptr<animal> a;
            ia >> a;
            cout << "a->legs(): " << a->legs() << '\n';
        };

        save();
        load();
    }

    cout << bold << underline << "Serializing references" << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            animal a{4};
            animal &r = a;
            oa << r;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            animal a;
            animal &r = a;
            ia >> r;
            cout << "r.legs(): " << r.legs() << '\n';
        };

        save();
        load();
    }

    cout << on_yellow << bold << underline
              << "Serialization of Class Hierarchy Objects"
              << reset << endl;
    cout << bold << underline << "Serializing derived classes correctly"
              << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            bird penguin{2, false};
            oa << penguin;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            bird penguin;
            ia >> penguin;
            cout << "penguin.legs(): " << penguin.legs() << '\n';
            cout << "boolalpha << penguin.can_fly(): " << boolalpha << penguin.can_fly() << '\n';
        };

        save();
        load();
    }

    cout << bold << underline
              << "Registering derived classes statically with BOOST_CLASS_EXPORT" << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            animal *a = new bird{2, false};
            oa << a;
            delete a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            animal *a;
            ia >> a;
            cout << "a->legs(): " << a->legs() << '\n';
            delete a;
        };

        save();
        load();
    }

    cout << bold << underline
              << "Registering derived classes dynamically with register_type()" << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            oa.register_type<bird>();
            animal *a = new bird{2, false};
            oa << a;
            delete a;
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            ia.register_type<bird>();
            animal *a;
            ia >> a;
            cout << "a->legs(): " << a->legs() << '\n';
            delete a;
        };

        save();
        load();
    }

    cout << on_yellow << bold << underline << "Wrapper Functions for Optimization"
              << reset << endl;

    cout << bold << underline << "Serializing an array without a wrapper function"
              << reset << endl;
    {
        stringstream ss;

        auto save = [&ss]() -> void {
            text_oarchive oa{ss};
            array<int, 3> a{{0, 1, 2}};
            oa << serialization::make_array(a.data(), a.size());
        };

        auto load = [&ss]() -> void {
            text_iarchive ia{ss};
            array<int, 3> a;
            ia >> serialization::make_array(a.data(), a.size());
            cout << "a[0] << \", \" << a[1] << \", \" << a[2]: " << a[0] << ", " << a[1] << ", " << a[2] << '\n';
        };

        save();
        load();
    }

    cout << bold << on_yellow << "Universally Unique Identifiers" << reset << endl;
    cout << on_yellow << bold << underline << "Boost.Uuid"
              << reset << endl;

    cout << bold << underline << "Generating random UUIDs with random_generator" << reset << endl;
    {
        random_generator gen;
        uuid id = gen();
        cout << "id: " << id << '\n';
    }

    cout << bold << underline << "Member functions of uuid" << reset << endl;
    {
        random_generator gen;
        uuid id = gen();
        cout << "id.size(): " << id.size() << '\n';
        cout << "boolalpha << id.is_nil(): " << boolalpha << id.is_nil() << '\n';
        cout << "id.variant(): " << id.variant() << '\n';
        cout << "id.version(): " << id.version() << '\n';
    }

    cout << bold << underline << "Generators from Boost.Uuid" << reset << endl;
    {
        nil_generator nil_gen;
        uuid id = nil_gen();
        cout << "boolalpha << id.is_nil(): " << boolalpha << id.is_nil() << '\n';

        string_generator string_gen;
        id = string_gen("CF77C981-F61B-7817-10FF-D916FCC3EAA4");
        cout << "id.variant(): " << id.variant() << '\n';

        name_generator name_gen(id);
        cout << "name_gen(\"theboostcpplibraries.com\"): " << name_gen("theboostcpplibraries.com") << '\n';
    }

    cout << bold << underline << "Conversion to strings" << reset << endl;
    {
        random_generator gen;
        uuid id = gen();

        string s = to_string(id);
        cout << "s: " << s << '\n';

        cout << "lexical_cast<string>(id): " << lexical_cast<string>(id) << '\n';
    }

    cout << bold << on_yellow << "Program Options" << reset << endl;

    cout << bold << underline << "Basic approach with Boost.ProgramOptions"
              << reset << endl;
    {
        try
        {
            auto on_age = [](int age)->void
            {
                cout << "On age: " << age << '\n';
            };

            options_description desc{"Options"};
            desc.add_options()
                        ("help,h", "Help screen")
                        ("pi", value<float>()->default_value(3.14f), "Pi")
                        ("age", value<int>()->notifier(on_age), "Age");

            variables_map vm;
            store(parse_command_line(argc, argv, desc), vm);
            notify(vm);

            if (vm.count("help"))
                cout << desc << '\n';
            else if (vm.count("age"))
                cout << "Age: " << vm["age"].as<int>() << '\n';
            else if (vm.count("pi"))
                cout << "Pi: " << vm["pi"].as<float>() << '\n';
        }
        catch (const runtime_error &ex)
        {
            cerr << ex.what() << '\n';
        }
    }

    cout << bold << underline << "Positional options with Boost.ProgramOptions" << reset << endl;
    {
        try
        {
            auto to_cout = [](const vector<string> &v)->void
            {
                copy(v.begin(), v.end(),
                          ostream_iterator<string>{cout, "\n"});
            };

            options_description desc{"Options"};
            desc.add_options()
                        ("help,h", "Help screen")
                        ("phone", value<vector<string>>()->
                                                                           multitoken()->zero_tokens()->composing(), "Phone");

            positional_options_description pos_desc;
            pos_desc.add("phone", -1);

            command_line_parser parser{argc, argv};
            parser.options(desc).positional(pos_desc).allow_unregistered();
            parsed_options parsed_options = parser.run();

            variables_map vm;
            store(parsed_options, vm);
            notify(vm);

            if (vm.count("help"))
                cout << desc << '\n';
            else if (vm.count("phone"))
                to_cout(vm["phone"].as<vector<string>>());
        }
        catch (const runtime_error &ex)
        {
            cerr << ex.what() << '\n';
        }
    }

    cout << bold << underline << "Loading options from a configuration file" << reset << endl;
    {
        try
        {
            options_description generalOptions{"General"};
            generalOptions.add_options()
                                  ("help,h", "Help screen")
                                  ("config", value<string>(), "Config file");

            options_description fileOptions{"File"};
            fileOptions.add_options()
                               ("age", value<int>(), "Age");

            variables_map vm;
            store(parse_command_line(argc, argv, generalOptions), vm);
            if (vm.count("config"))
            {
                ifstream ifs{vm["config"].as<string>().c_str()};
                if (ifs)
                    store(parse_config_file(ifs, fileOptions), vm);
            }
            notify(vm);

            if (vm.count("help"))
                cout << generalOptions << '\n';
            else if (vm.count("age"))
                cout << "Your age is: " << vm["age"].as<int>() << '\n';
        }
        catch (const runtime_error &ex)
        {
            cerr << ex.what() << '\n';
        }
    }
    return 0;
}
