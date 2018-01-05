#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

#include "utils.h"

using namespace std;
using namespace utl;

int main()
{
    cout << bold << on_yellow << "Range-based Algorithms" << reset << endl;
    cout << bold << underline << "Range algorithms related to algorithms from the standard library" << reset << endl;
    {
        array<int, 6> a{{0, 1, 2, 3, 4, 5}};
        cout << count(a, 0) << '\n';
        random_shuffle(a);
        cout << "random_shuffle(): " << endl;
        copy(a.begin(), a.end(), ostream_iterator<int>{cout, ","});
        cout << "\n" << "*max_element(a): " << *max_element(a) << '\n';
        cout << "accumulate(a, 0): " << accumulate(a, 0) << '\n';
        sort(a);
        copy(a.begin(), a.end(), ostream_iterator<int>{cout, ","});
        cout << "\n";
    }

    cout << on_yellow << bold << underline << "Shortcuts for STL algorithms" << reset << endl;
    {
        cout << bold << underline << "Creating vector" << reset << endl;
        cout << "vector<int> a = perm(10);" << endl;
        vector<int> a = perm(10);
        cout << "a: " << a << endl;

        cout << bold << underline << "Sorting" << reset << endl;
        {
            cout << "partial_sort(a,a.begin()+5);" << endl;
            partial_sort(a,a.begin()+5);
            cout << "a: " << a << endl;
            cout << "sort(a);" << endl;
            sort(a);
            cout << "a: " << a << endl;
            cout << boolalpha << "is_sorted(a): " << is_sorted(a) << '\n';
            cout << boolalpha << "binary_search(a,3): " << binary_search(a,3) << '\n';
            cout << boolalpha << "lower_bound(a,3)-a.begin(): " << lower_bound(a,3)-a.begin() << '\n';

        }

        cout << bold << underline << "Non-modifying sequence operations" << reset << endl;
        {
            cout << "count(a, 0): " << count(a, 0) << '\n';
            cout << "find(a, 1)-a.begin(): " << find(a, 1)-a.begin() << '\n';
            cout << "*max_element(a): " << *max_element(a) << '\n';
            cout << "max_element(a)-a.begin(): " << max_element(a)-a.begin() << '\n';
            cout << "accumulate(a, 0): " << accumulate(a, 0) << '\n';

        }

        cout << bold << underline << "Modifying sequence operationsry" << reset << endl;
        {
            cout << "random_shuffle(a);" << endl;
            random_shuffle(a);
            cout << "a: " << a << endl;
            cout << "deque<int> d;" << endl;
            deque<int> d;
            cout << "push_back(d, a);" << endl;
            push_back(d, a);
            cout << "remove_erase(d, 2);" << endl;
            remove_erase(d, 2);
            cout << "a: " << a << endl;
        }

    }

    cout << bold << underline << "Range algorithms without counterparts in the standard library" << reset << endl;
    {
        array<int, 6> a{{0, 1, 2, 3, 4, 5}};
        cout << boolalpha << "is_sorted(a)" << is_sorted(a) << '\n';
        deque<int> d;
        push_back(d, a);
        remove_erase(d, 2);
        for (auto &&item : d) {
            cout << item << ",";
        }
        cout << endl;
    }

    cout << bold << on_yellow << "Range-based views" << reset << endl;
    cout << bold << underline << "Filtering a range" << reset << endl;
    {
        array<int, 6> a{{0, 5, 2, 1, 3, 4}};
        cout << "view::filter(a,[](int i){ return i > 2; }): " << endl;
        copy(view::reverse(a), ostream_iterator<int>{cout, ","});
        cout << endl;
        copy(view::filter(a, [](int i){ return i > 2; }), ostream_iterator<int>{cout, ","});
        cout << endl;
        copy(a | view::reversed, ostream_iterator<int>{cout, ","});
        cout << endl;
        copy(a | view::reversed | view::uniqued, ostream_iterator<int>{cout, ","});
        cout << endl;
        vector<int> b{{0,1,2,3}};
        push_back(b, a | view::reversed);
        copy(b, ostream_iterator<int>{cout, ","});
        cout << endl;
        copy(view::join(a,b), ostream_iterator<int>{cout, ","});
        cout << endl;
    }

    cout << bold << underline << "Filter for container keys, values, and indirect pointees" << reset << endl;
    {
        array<int, 3> a{{0, 1, 2}};
        map<string, int*> m;
        m.insert(make_pair("a", &a[0]));
        m.insert(make_pair("b", &a[1]));
        m.insert(make_pair("c", &a[2]));

        cout << "Access keys and values in a container directly and indirectly:" << endl;
        copy(view::keys(m), ostream_iterator<string>{cout, ","});
        copy(view::values(m), ostream_iterator<int*>{cout, ","});
        copy(view::indirect(view::values(m)), ostream_iterator<int>{cout, ","});
    }

    cout << bold << underline << "Create iterator for (boost) regex tokens on strings" << reset << endl;
    {
        string s = "The Boost C++ Libraries";
        boost_regex expr{"[\\w+]+"};
        copy(view::tokenize(s, expr, 0, boost_regex_constants::match_default), ostream_iterator<string>{cout, ","});
        cout << endl;
    }

    cout << bold << underline << "Ranges of integers (without having to use a container)" << reset << endl;
    {
        view::integer_range<int> ir = view::irange(0, 10);
        cout << "integer_range<int>: " << endl;
        copy(ir, ostream_iterator<int>{cout, ","});
        cout << endl;
        // or ...
        for (auto &&item : view::irange(0, 10)) {
            cout << item << " ";
        }
        cout << endl;
    }

    /*
    cout << bold << underline << "Ranges from the input stream" << reset << endl;
    {
        view::iterator_range<istream_iterator<int>> ir = istream_range<int>(cin);
        copy(ir, ostream_iterator<int>{cout, "\n"});
    }
    */

    cout << bold << underline << "Ranges defined by subranges" << reset << endl;
    {
        array<int, 6> a{{0, 1, 2, 3, 4, 5}};
        view::iterator_range<array<int, 6>::iterator> r1 = random_shuffle(a);
        view::sub_range<array<int, 6>> r2 = random_shuffle(r1);
        copy(r2, ostream_iterator<int>{cout, ","});
        cout << endl;
    }

    cout << bold << on_yellow << "Extension to STL algorithms" << reset << endl;
    cout << bold << underline << "Testing a condition in the whole container" << reset << endl;
    {
        array<int, 6> a = {0, 5, 2, 1, 4, 3};
        auto predicate = [](int i) { return i == 4; };
        cout.setf(ios::boolalpha);
        cout << "any_of(a, predicate): " << any_of(a, predicate) << '\n';
        cout << "any_of(a.begin(), a.end(), predicate): " << any_of(a.begin(), a.end(), predicate) << '\n';
        cout << "any_of(a.begin(), a.end(), 4): " << any_of_equal(a.begin(), a.end(), 4) << '\n';
        cout << "any_of(a, 4): " << any_of_equal(a, 4) << '\n';
        cout << "is_sorted(a): " << is_sorted(a) << '\n';
        sort(a);
        cout << "sort(a);" << '\n';
        cout << "is_sorted(a): " << is_sorted(a) << '\n';
    }

    cout << bold << on_yellow << "Hexadecimal conversion" << reset << endl;
    cout << bold << underline << "Converting hexadecimal numbers and strings" << reset << endl;
    {
        // convert characters to hexadecimal values
        vector<char> v{'C', '+', '+'};
        cout << "vector<char> v" << v << endl << "hex: ";
        hex(v, ostream_iterator<char>{cout, ""});
        cout << '\n';

        string s = "C++";
        cout << "string s: " << s << endl;
        cout << "hex: " << hex(s) << '\n';

        vector<int> n = {4};
        cout << "vector<int> n: " << n << endl;
        cout << "hex(n): " << hex(n) << '\n';
        cout << "unhex(hex(n)): " << unhex(hex(n)) << '\n';

        vector<char> w{'4', '3', '2', 'b', '2', 'b'};
        cout << "vector<char> w: " << w << endl << "unhex: ";
        unhex(w, ostream_iterator<char>{cout, ""});
        cout << '\n';

        string t = "432b2b";
        cout << "string t: " << t << endl;
        cout << "unhex: " << unhex(t) << '\n';
    }

    struct base1 { virtual ~base1() = default; };
    struct base2 { virtual ~base2() = default; };
    struct derived : public base1, public base2 {};

    cout << bold << on_yellow << "Polymorphic Casting" << reset << endl;
    cout << bold << underline << "Casting Algorithms to down and cross casts with dynamic_cast" << reset << endl;
    {
        auto downcast = [](base1 *b1)
        {
            derived *d = dynamic_cast<derived*>(b1);
        };

        auto crosscast = [](base1 *b1)
        {
            base2 *b2 = dynamic_cast<base2*>(b1);
        };

        derived *d = new derived;
        downcast(d);

        base1 *b1 = new derived;
        crosscast(b1);
    }

    cout << bold << underline << "Down and cross casts with polymorphic_downcast and polymorphic_cast" << reset << endl;
    {
        auto downcast = [](base1 *b1)
        {
            derived *d = polymorphic_downcast<derived*>(b1);
        };

        auto crosscast = [](base1 *b1)
        {
            base2 *b2 = polymorphic_cast<base2*>(b1);
        };

        derived *d = new derived;
        downcast(d);

        base1 *b1 = new derived;
        crosscast(b1);
    }

    return 0;
}
