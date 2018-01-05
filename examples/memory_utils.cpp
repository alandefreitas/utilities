#include <list>
#include <vector>
#include <string>
#include <vector>
#include <utility>

#include "utils.h"

using namespace std;
using namespace utl;

struct int_pool {};

typedef singleton_pool<int_pool, sizeof(int)> singleton_int_pool;

struct person_ {
    int id_;
    string city_;
};

struct person {
    int id_;
    flyweight<string> city_;

    person(int id, string city) : id_{id}, city_{move(city)} {}
};

struct located_person {
    int id_;
    flyweight<string> city_;
    flyweight<string> country_;

    located_person(int id, string city, string country)
            : id_{id}, city_{move(city)}, country_{move(country)} {}
};

struct city {};
struct country {};

struct tagged_person {
    int id_;
    flyweight<string, flyweights::tag<city>> city_;
    flyweight<string, flyweights::tag<country>> country_;

    tagged_person(int id, string city, string country)
            : id_{id}, city_{move(city)}, country_{move(country)} {}
};

struct templated_person {
    int id_;
    flyweight<string, flyweights::set_factory<>, flyweights::no_locking, flyweights::no_tracking> city_;
    // set_factory -> sorted container
    // no_locking -> no multithreading
    // no_tracking -> not deleting objects stored in internal containers (when they're no longer used)
    templated_person(int id, string city) : id_{id}, city_{move(city)} {}
};

int main()
{
    cout << bold << on_yellow << "Memory Pool" << reset << endl;

    cout << bold << underline << "Using boost::object_pool" << reset << endl;
    {
        boost::object_pool<int> pool;

        int *i = pool.malloc();
        *i = 1;

        int *j = pool.construct(2);

        pool.destroy(i);
        pool.destroy(j);
    }

    cout << bold << underline << "Changing the segment size with boost::object_pool" << reset << endl;
    {
        boost::object_pool<int> pool{32, 0};
        pool.construct();
        cout << pool.get_next_size() << '\n';
        pool.set_next_size(8);
    }
    cout << bold << underline << "Using boost::singleton_pool" << reset << endl;
    {
        int *i = static_cast<int*>(singleton_int_pool::malloc());
        *i = 1;

        int *j = static_cast<int*>(singleton_int_pool::ordered_malloc(10));
        j[9] = 2;

        singleton_int_pool::release_memory();
        singleton_int_pool::purge_memory();
    }
    cout << bold << underline << "Using boost::pool_allocator" << reset << endl;
    {
        vector<int, boost::pool_allocator<int>> v;
        for (int i = 0; i < 1000; ++i)
            v.push_back(i);

        v.clear();
        boost::singleton_pool<boost::pool_allocator_tag, sizeof(int)>::
        purge_memory();
    }
    cout << bold << underline << "Using boost::fast_pool_allocator" << reset << endl;
    {
        typedef boost::fast_pool_allocator<int,
                boost::default_user_allocator_new_delete,
                boost::details::pool::default_mutex,
                64, 128> allocator;

        list<int, allocator> l;
        for (int i = 0; i < 1000; ++i)
            l.push_back(i);

        l.clear();
        boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(int)>::
        purge_memory();
    }

    cout << bold << on_yellow << "Flyweight Pattern (avoiding replicate data in objects)" << reset << endl;
    cout << bold << underline
              << "A hundred thousand identical strings without Boost.Flyweight" << reset << endl;
    {
        vector<person_> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin"});
        }
    }

    cout << bold << underline
              << "One string instead of a hundred thousand strings with Boost.Flyweight" << reset
              << endl;
    {
        vector<person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin"});
        }
    }

    cout << bold << underline << "Using boost::flyweights::flyweight multiple times" << reset << endl;
    {
        vector<located_person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin", "Germany"});
        }
    }

    cout << bold << underline
              << "Using boost::flyweights multiple times with tags" << reset << endl;
    {
        vector<tagged_person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin", "Germany"});
        }

    }

    cout << bold << underline << "Template parameters of boost::flyweights::flyweight" << reset << endl;
    {
        vector<templated_person> persons;
        for (int i = 0; i < 100000; ++i) {
            persons.push_back({i, "Berlin"});
        }
    }

    return 0;
}
