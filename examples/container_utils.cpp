#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>

#include "utils.h"

using namespace std;
using namespace utl;

struct animal {
    string name;
    int legs;
};

int main() {
    cout << bold << on_yellow << "Graphs" << reset << endl;
    cout << bold << underline << "Directed Graphs" << reset << endl;
    {
        directed_graph g;
        g.add_vertex();
        g.add_vertex();
        directed_graph::vertex v1 = g.add_vertex();
        directed_graph::vertex v2 = g.add_vertex();
        g.add_edge(v1, v2);
        g.add_edge(1, 2);
        g.add_edge(1, 0);
        g.print_vertices();
        g.print_edges();
        g.print_adjacent(v1);
        g.print_in_edges(v1);
        g.print_out_edges(v1);
    }
    cout << bold << underline << "Undirected Graphs" << reset << endl;
    {
        undirected_graph g;
        g.add_vertex();
        g.add_vertex();
        undirected_graph::vertex v1 = g.add_vertex();
        undirected_graph::vertex v2 = g.add_vertex();
        g.add_edge(v1, v2);
        g.add_edge(1, 2);
        g.add_edge(1, 0);
        g.print_vertices();
        g.print_edges();
        g.print_adjacent(v1);
    }

    cout << bold << on_yellow << "Bidirectional maps" << reset << endl;
    cout << bold << underline << "Using bimap" << reset << endl;
    {
        bimap<string, int> animals;
        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});
        cout << animals.left.count("cat") << '\n';
        cout << animals.right.count(8) << '\n';
    }

    cout << bold << underline << "Accessing relations" << reset << endl;
    {
        bimap<string, int> animals;
        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});
        for (auto it = animals.begin(); it != animals.end(); ++it) {
            cout << it->left << " has " << it->right << " legs\n";
        }
    }
    cout << bold << underline << "Using set_of explicitly" << reset << endl;
    {
        bimap<set_of<string>, set_of<int>> animals;
        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});
        cout << animals.left.count("spider") << '\n';
        cout << animals.right.count(8) << '\n';
    }

    cout << bold << underline << "Allowing duplicates with multiset_of" << reset << endl;
    {
        bimap<set_of<string>, multiset_of<int>> animals;
        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"dog", 4});
        cout << animals.left.count("dog") << '\n';
        cout << animals.right.count(4) << '\n';
    }
    cout << bold << underline << "Disabling one side with unconstrained_set_of" << reset << endl;
    {
        bimap<string, unconstrained_set_of<int>> animals;
        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});
        auto it = animals.left.find("cat");
        animals.left.modify_key(it, _key = "dog");
        cout << it->first << '\n';
    }

    cout << bold << on_yellow << "Multidimensional arrays" << reset << endl;
    cout << bold << underline << "One-dimensional array with multi_array" << reset << endl;
    {
        multi_array<char, 1> a{extents[6]};
        a[0] = 'B';
        a[1] = 'o';
        a[2] = 'o';
        a[3] = 's';
        a[4] = 't';
        a[5] = '\0';
        cout << "a.origin() (or &a[0]): " << a.origin() << '\n';
    }
    cout << bold << underline << "Views and subarrays of a two-dimensional array" << reset << endl;
    {
        multi_array<char, 2> a{extents[2][6]};
        multi_array<char, 2>::array_view<1>::type view = a[indices[0][multi_array_types::index_range{0, 5}]];

        memcpy(view.origin(), "tsooB", 6);
        reverse(view.begin(), view.end());
        cout << "view.origin(): " << view.origin() << '\n';

        multi_array<char, 2>::reference subarray = a[1];
        memcpy(subarray.origin(), "C++", 4);

        cout << "subarray.origin(): " << subarray.origin() << '\n';
    }
    cout << bold << underline << "Wrapping a C array with multi_array_ref" << reset << endl;
    {
        char c[12] =
                {
                        't', 's', 'o', 'o', 'B', '\0',
                        'C', '+', '+', '\0', '\0', '\0'
                };

        multi_array_ref<char, 2> a{c, extents[2][6]};
        multi_array<char, 2>::array_view<1>::type view = a[indices[0][multi_array_types::index_range{0, 5}]];

        reverse(view.begin(), view.end());
        cout << "view.origin(): " << view.origin() << '\n';

        multi_array<char, 2>::reference subarray = a[1];
        cout << "subarray.origin(): " << subarray.origin() << '\n';
    }


    cout << bold << on_yellow << "Recursive and stable containers" << reset << endl;
    cout << bold << underline << "Recursive containers with Boost.Container" << reset << endl;
    {
        struct mammal {
            recursive::vector<mammal> children;
        };
        mammal parent, child1, child2;
        parent.children.push_back(child1);
        parent.children.push_back(child2);
    }
    cout << bold << underline << "Using container::stable_vector" << reset << endl;
    {
        stable_vector<int> v(2, 1);
        int &i = v[1];
        v.erase(v.begin());
        cout << i << '\n';
    }

    cout << bold << on_yellow << "Multi-index" << reset << endl;
    cout << bold << underline << "Using multi_index::multi_index_container" << reset << endl;
    {
        typedef multi_index_container<animal, indexed_by<hashed_non_unique<member<animal, string, &animal::name>>, hashed_non_unique<member<animal, int, &animal::legs>>>> animal_multi;

        animal_multi animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});
        cout << animals.count("cat") << '\n';

        const animal_multi::nth_index<1>::type &legs_index = animals.get<1>();
        cout << legs_index.count(8) << '\n';
    }

    cout << bold << underline << "Changing elements in a MultiIndex container with modify()" << reset << endl;
    {
        typedef multi_index_container<animal, indexed_by<hashed_non_unique<member<animal, string, &animal::name>>, hashed_non_unique<member<animal, int, &animal::legs>>>> animal_multi;

        animal_multi animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"spider", 8});

        auto &legs_index = animals.get<1>();
        auto it = legs_index.find(4);
        legs_index.modify(it, [](animal &a) { a.name = "dog"; });

        cout << animals.count("dog") << '\n';
    }

    cout << bold << underline << "A MultiIndex container with multi_index::hashed_unique" << reset << endl;
    {
        typedef multi_index_container<animal, indexed_by<hashed_non_unique<member<animal, string, &animal::name>>, hashed_unique<member<animal, int, &animal::legs>>>> animal_multi2;
        animal_multi2 animals;

        animals.insert({"cat", 4});
        animals.insert({"shark", 0});
        animals.insert({"dog", 4});

        auto &legs_index = animals.get<1>();
        cout << legs_index.count(4) << '\n';
    }

    cout << bold << on_yellow << "Circular Buffer" << reset << endl;
    cout << bold << underline << "Using circular_buffer" << reset << endl;
    {
        circular_buffer<int> cb{3};

        cout << "cb.capacity() : " << cb.capacity() << endl;
        cout << "cb.size() : " << cb.size() << endl;

        cb.push_back(0);
        cb.push_back(1);
        cb.push_back(2);

        cout << "cb.size() : " << cb.size() << endl;

        cb.push_back(3);
        cb.push_back(4);
        cb.push_back(5);

        cout << "cb.size() : " << cb.size() << endl;

        for (int i : cb) {
            cout << "i : " << i << endl;
        }
    }

    cout << bold << underline << "Various member functions of circular_buffer" << reset << endl;
    {
        typedef circular_buffer<int> circular_buffer;
        circular_buffer cb{3};

        cb.push_back(0);
        cb.push_back(1);
        cb.push_back(2);
        cb.push_back(3);

        // true if the beginning of the circular buffer is at the lowest memory address
        cout << boolalpha << "cb.is_linearized(): " << cb.is_linearized() << '\n';

        // Both array_one() and array_two() return a pair whose first element is a pointer to the corresponding array and whose second element is the size
        circular_buffer::array_range ar1, ar2;

        // array_one() accesses the array at the beginning of the circular buffer, and array_two() accesses the array at the end of the buffer
        ar1 = cb.array_one();
        ar2 = cb.array_two();

        cout << ar1.second << ";" << ar2.second << '\n';

        for (int i : cb) {
            cout << i << '\n';
        }

        // force a rearrangement of the elements by calling linearize()
        cb.linearize();

        ar1 = cb.array_one();
        ar2 = cb.array_two();
        cout << ar1.second << ";" << ar2.second << '\n';
    }

    cout << bold << on_yellow << "Heaps" << reset << endl;

    // In general this class behaves like priority_queue, except it allows you to iterate over elements
    cout << bold << underline << "Using heap::priority_queue" << reset << endl;
    {
        heap::priority_queue<int> pq;
        pq.push(2);
        pq.push(3);
        pq.push(1);

        for (int i : pq) {
            cout << "i : " << i << endl;
        }

        heap::priority_queue<int> pq2;
        pq2.push(4);
        cout << boolalpha << "(pq > pq2): " << (pq > pq2) << endl;
    }

    // In addition to allowing you to iterate over elements in priority order, it also lets you merge priority queues
    cout << bold << underline << "Using heap::binomial_heap" << reset << endl;
    {
        binomial_heap<int> bh;
        bh.push(2);
        bh.push(3);
        bh.push(1);

        binomial_heap<int> bh2;
        bh2.push(4);
        bh.merge(bh2);

        for (auto it = bh.ordered_begin(); it != bh.ordered_end(); ++it) {
            cout << "*it : " << *it << endl;
        }
        cout << boolalpha << "bh2.empty(): " << bh2.empty() << endl;
    }

    cout << bold << underline << "Changing elements in binomial_heap" << reset << endl;
    {
        binomial_heap<int> bh;
        auto handle = bh.push(2);
        bh.push(3);
        bh.push(1);

        bh.update(handle, 4);
        cout << "bh.top() : " << bh.top() << endl;
    }

    return 0;
}