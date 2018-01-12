#include <chrono>
#include <thread>
#include <memory>
#include <functional>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

#include "utils.h"

using namespace std;
using namespace utl;

int main()
{
    const bool run_interprocess_examples = false;

    asio::io_service ioservice;
    tcp::resolver resolv{ioservice};
    tcp::socket tcp_socket{ioservice};
    array<char, 4096> bytes;

    tcp::endpoint tcp_endpoint{tcp::v4(), 2014};
    tcp::acceptor tcp_acceptor{ioservice, tcp_endpoint};
    string data;

    cout << bold << on_yellow << "ASIO" << reset << endl;

    cout << bold << underline << "ASIO's steady timer" << reset
              << endl;
    {
        asio::io_service ioservice;
        asio::steady_timer timer{ioservice, chrono::seconds{3}};
        timer.async_wait([](const boost::system::error_code &ec) { cout << "3 sec\n"; });
        ioservice.run();
    }

    cout << bold << underline << "Two asynchronous ASIO's steady timer" << reset << endl;
    {
        asio::io_service ioservice;
        asio::steady_timer timer1{ioservice, chrono::seconds{3}};
        timer1.async_wait([](const boost::system::error_code &ec) { cout << "3 sec\n"; });
        asio::steady_timer timer2{ioservice, chrono::seconds{4}};
        timer2.async_wait([](const boost::system::error_code &ec) { cout << "4 sec\n"; });
        ioservice.run();
    }

    cout << bold << underline << "Two asynchronous ASIO's steady timers running on threads" << reset << endl;
    {
        asio::io_service ioservice;
        asio::steady_timer timer1{ioservice, chrono::seconds{3}};
        timer1.async_wait([](const boost::system::error_code &ec) { cout << "3 sec\n"; });
        asio::steady_timer timer2{ioservice, chrono::seconds{4}};
        timer2.async_wait([](const boost::system::error_code &ec) { cout << "4 sec\n"; });
        // run() is called on the only I/O service object in each thread
        // I/O service object to use both threads to execute handlers
        // Calling run() repeatedly on a single I/O service object is the recommended method to make a program based on Boost.Asio more scalable.
        thread thread1{[&ioservice]() { ioservice.run(); }};
        thread thread2{[&ioservice]() { ioservice.run(); }};
        thread1.join();
        thread2.join();
    }

    cout << bold << underline << "One thread for each of two I/O service objects to execute handlers concurrently" << reset << endl;
    {
        // However, instead of providing several threads to one I/O service object, you could also create multiple I/O service objects.
        asio::io_service ioservice1;
        asio::io_service ioservice2;
        asio::steady_timer timer1{ioservice1, chrono::seconds{3}};
        timer1.async_wait([](const boost::system::error_code &ec) { cout << "3 sec\n"; });
        asio::steady_timer timer2{ioservice2, chrono::seconds{3}};
        timer2.async_wait([](const boost::system::error_code &ec) { cout << "3 sec\n"; });
        thread thread1{[&ioservice1]() { ioservice1.run(); }};
        thread thread2{[&ioservice2]() { ioservice2.run(); }};
        thread1.join();
        thread2.join();
    }

    cout << bold << on_yellow << "ASIO Web Client" << reset << endl;

    cout << bold << underline << "A web client with boost::asio::ip::tcp::socket" << reset << endl;
    {
        cout << "Even though Boost.Asio can process any kind of data asynchronously, it is mainly used for network programming" << endl;

        function<void(const boost::system::error_code,size_t)> read_handler;
        read_handler = [&read_handler, &bytes, &tcp_socket](const boost::system::error_code &ec,
                                       size_t bytes_transferred) {
            if (!ec) {
                cout.write(bytes.data(), bytes_transferred);
                tcp_socket.async_read_some(asio::buffer(bytes), read_handler);
            }
        };

        auto connect_handler = [&read_handler, &tcp_socket, &bytes](const boost::system::error_code &ec) {
            if (!ec) {
                string r =
                        "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
                write(tcp_socket, asio::buffer(r));
                tcp_socket.async_read_some(asio::buffer(bytes), read_handler);
            }
        };

        auto resolve_handler = [&connect_handler, &tcp_socket](const boost::system::error_code &ec,
                                                  tcp::resolver::iterator it) {
            if (!ec) {
                tcp_socket.async_connect(*it, connect_handler);
            }
        };

        tcp::resolver::query q{"theboostcpplibraries.com", "80"};
        resolv.async_resolve(q, resolve_handler);
        ioservice.run();
    }

    cout << bold << underline << "A time server with boost::asio::ip::tcp::acceptor"
              << reset << endl;
    {

        function<void(const boost::system::error_code,size_t)> write_handler;
        write_handler = [&write_handler, &tcp_socket](const boost::system::error_code &ec,size_t bytes_transferred) {
            if (!ec) {
                tcp_socket.shutdown(tcp::socket::shutdown_send);
            }
        };

        function<void(const boost::system::error_code)> accept_handler;
        accept_handler = [&write_handler, &data, &tcp_socket](const boost::system::error_code &ec) {
            if (!ec) {
                time_t now = time(nullptr);
                data = ctime(&now);
                async_write(tcp_socket, asio::buffer(data), write_handler);
            }
        };

        tcp_acceptor.listen();
        tcp_acceptor.async_accept(tcp_socket, accept_handler);
        ioservice.run();
    }

    if (run_interprocess_examples){

        cout << bold << on_yellow << "Interprocesses with shared memory" << reset << endl;

        cout << bold << underline << "Creating shared memory" << reset
             << endl;
        {
            interprocess::shared_memory_object shdmem{interprocess::open_or_create, "Boost", interprocess::read_write};
            shdmem.truncate(1024);
            cout << shdmem.get_name() << '\n';
            interprocess::offset_t size;
            if (shdmem.get_size(size))
                cout << size << '\n';
        }

        cout << bold << underline << "Mapping shared memory into the address space of a process" << reset << endl;
        {
            interprocess::shared_memory_object shdmem{interprocess::open_or_create, "Boost", interprocess::read_write};
            shdmem.truncate(1024);
            interprocess::mapped_region region{shdmem, interprocess::read_write};
            cout << hex << region.get_address() << '\n';
            cout << dec << region.get_size() << '\n';
            interprocess::mapped_region region2{shdmem, interprocess::read_only};
            cout << hex << region2.get_address() << '\n';
            cout << dec << region2.get_size() << '\n';
        }

        cout << bold << underline << "Writing and reading a number in shared memory" << reset << endl;
        {
            interprocess::shared_memory_object shdmem{interprocess::open_or_create, "Boost", interprocess::read_write};
            shdmem.truncate(1024);
            interprocess::mapped_region region{shdmem, interprocess::read_write};
            int *i1 = static_cast<int*>(region.get_address());
            *i1 = 99;
            interprocess::mapped_region region2{shdmem, interprocess::read_only};
            int *i2 = static_cast<int*>(region2.get_address());
            cout << *i2 << '\n';
        }

        cout << bold << underline << "Deleting shared memory" << reset << endl;
        {
            bool removed = interprocess::shared_memory_object::remove("Boost");
            cout << boolalpha << removed << '\n';
        }

        cout << bold << underline << "Using managed shared memory" << reset << endl;
        {
            interprocess::shared_memory_object::remove("Boost");
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "Boost", 1024};
            int *i = managed_shm.construct<int>("Integer")(99);
            cout << *i << '\n';
            pair<int*, size_t> p = managed_shm.find<int>("Integer");
            if (p.first)
                cout << *p.first << '\n';
        }

        cout << bold << underline << "Creating arrays in managed shared memory" << reset << endl;
        {
            interprocess::shared_memory_object::remove("Boost");
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "Boost", 1024};
            int *i = managed_shm.construct<int>("Integer")[10](99);
            cout << *i << '\n';
            pair<int*, size_t> p = managed_shm.find<int>("Integer");
            if (p.first)
            {
                cout << *p.first << '\n';
                cout << p.second << '\n';
            }
        }

        cout << bold << underline << "An exception of type boost::interprocess::bad_alloc" << reset << endl;
        {
            try
            {
                interprocess::shared_memory_object::remove("Boost");
                interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "Boost", 1024};
                int *i = managed_shm.construct<int>("Integer")[4096](99);
            }
            catch (boost::interprocess::bad_alloc &ex)
            {
                cerr << ex.what() << '\n';
            }
        }

        cout << bold << underline << "Removing objects in shared memory" << reset << endl;
        {
            interprocess::shared_memory_object::remove("Boost");
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "Boost", 1024};
            int *i = managed_shm.find_or_construct<int>("Integer")(99);
            cout << *i << '\n';
            managed_shm.destroy<int>("Integer");
            pair<int*, size_t> p = managed_shm.find<int>("Integer");
            cout << p.first << '\n';
        }

        cout << bold << underline << "Putting strings into shared memory" << reset << endl;
        {
            interprocess::shared_memory_object::remove("Boost");
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "shm_1", 1024};
            typedef interprocess::allocator<char, interprocess::managed_shared_memory::segment_manager> CharAllocator;
            typedef interprocess::basic_string<char, std::char_traits<char>, CharAllocator> string;
            string *s = managed_shm.find_or_construct<string>("String")("Hello!",
                                                                        managed_shm.get_segment_manager());
            s->insert(5, ", world");
            cout << *s << '\n';
        }

        cout << bold << underline << "Atomic access on a managed shared memory" << reset << endl;
        {
            auto construct_objects = [](interprocess::managed_shared_memory &managed_shm)
            {
                managed_shm.construct<int>("Integer")(99);
                managed_shm.construct<float>("Float")(3.14);
            };
            interprocess::shared_memory_object::remove("Boost");
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "shm_2", 1024};
            auto atomic_construct = bind(construct_objects, ref(managed_shm));
            managed_shm.atomic_func(atomic_construct);
            cout << *managed_shm.find<int>("Integer").first << '\n';
            cout << *managed_shm.find<float>("Float").first << '\n';
        }

        cout << bold << underline << "Using a named mutex with boost::interprocess::interprocess::named_mutex" << reset << endl;
        {
            cout << "Creating shared memory" << endl;
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "shm_3", 1024};
            cout << "Creating int on shared memory" << endl;
            int *i = managed_shm.find_or_construct<int>("Integer")();
            cout << "Creating named mutex" << endl;
            interprocess::named_mutex named_mtx{interprocess::open_or_create, "my_mutex_"};
            cout << "Locking named mutex" << endl;
            named_mtx.lock();
            cout << "Increasing the integer" << endl;
            ++(*i);
            cout << *i << '\n';
            cout << "Unlocking named mutex" << endl;
            named_mtx.unlock();
        }

        cout << bold << underline << "Using an anonymous mutex with interprocess::interprocess_mutex" << reset << endl;
        {
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "shm_4", 1024};
            int *i = managed_shm.find_or_construct<int>("Integer")();
            interprocess::interprocess_mutex *mtx =
                    managed_shm.find_or_construct<interprocess::interprocess_mutex>("my_mutex_2")();
            mtx->lock();
            ++(*i);
            cout << *i << '\n';
            mtx->unlock();
        }

        cout << bold << underline << "Using a named condition with boost::interprocess::interprocess::named_condition" << reset << endl;
        {
            cout << "Creating managed memory" << endl;
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "shm_5", 1024};
            cout << "Creating integer on shared memory" << endl;
            int *i = managed_shm.find_or_construct<int>("Integer")(0);
            cout << "Creating named mutex" << endl;
            interprocess::named_mutex named_mtx{interprocess::open_or_create, "my_mutex_3"};
            cout << "Creating lock for named mutex" << endl;
            interprocess::scoped_lock<interprocess::named_mutex> lock{named_mtx};
            cout << "Creating named condition" << endl;
            interprocess::named_condition named_cnd{interprocess::open_or_create, "condition_1"};
            cout << "while (*i < 10)" << endl;
            while (*i < 10)
            {
                if (*i % 2 == 0)
                {
                    cout << "*i is even" << endl;
                    ++(*i);
                    cout << "named_cnd.notify_all();" << endl;
                    named_cnd.notify_all();
                    cout << "named_cnd.wait(lock);" << endl;
                    named_cnd.wait(lock);
                }
                else
                {
                    cout << "*i is odd" << endl;
                    cout << *i << endl;
                    ++(*i);
                    cout << "named_cnd.notify_all();" << endl;
                    named_cnd.notify_all();
                    cout << "named_cnd.wait(lock);" << endl;
                    named_cnd.wait(lock);
                }
            }
            cout << "named_cnd.notify_all();" << endl;
            named_cnd.notify_all();
            interprocess::shared_memory_object::remove("shm_5");
            interprocess::named_mutex::remove("my_mutex_3");
            interprocess::named_condition::remove("condition_1");
        }

        cout << bold << underline << "Using an anonymous condition with interprocess::interprocess_condition" << reset << endl;
        {
            interprocess::managed_shared_memory managed_shm{interprocess::open_or_create, "shm_6", 1024};
            int *i = managed_shm.find_or_construct<int>("Integer")(0);
            interprocess::interprocess_mutex *mtx =
                    managed_shm.find_or_construct<interprocess::interprocess_mutex>("my_mutex_4")();
            interprocess::interprocess_condition *cnd =
                    managed_shm.find_or_construct<interprocess::interprocess_condition>("condition_2")();
            interprocess::scoped_lock<interprocess::interprocess_mutex> lock{*mtx};
            while (*i < 10)
            {
                if (*i % 2 == 0)
                {
                    ++(*i);
                    cnd->notify_all();
                    cnd->wait(lock);
                }
                else
                {
                    cout << *i << endl;
                    ++(*i);
                    cnd->notify_all();
                    cnd->wait(lock);
                }
            }
            cnd->notify_all();
            interprocess::shared_memory_object::remove("shm_6");
        }
    }


    cout << bold << on_yellow << "Simple HTTP Server" << reset << endl;
    http_server server;
    server.config.port=8080;
    cout << bold << underline << "HTTP server with simple GET route" << reset << endl;
    server.resource["^/info$"]["GET"] = [](shared_ptr<http_server::Response> response, shared_ptr<http_server::Request> request) {
        stringstream stream;
        stream << "<h1>Request from " << request->remote_endpoint_address() << ":" << request->remote_endpoint_port() << "</h1>";
        stream << request->method << " " << request->path << " HTTP/" << request->http_version;
        stream << "<h2>Query Fields</h2>";
        auto query_fields = request->parse_query_string();
        for(auto &field : query_fields)
            stream << field.first << ": " << field.second << "<br>";
        stream << "<h2>Header Fields</h2>";
        for(auto &field : request->header)
            stream << field.first << ": " << field.second << "<br>";
        response->write(stream);
    };

    cout << bold << underline << "HTTP server with regex GET route" << reset << endl;
    server.resource["^/match/([0-9]+)$"]["GET"] = [](shared_ptr<http_server::Response> response, shared_ptr<http_server::Request> request) {
        response->write(request->path_match[1]);
    };

    cout << bold << underline << "HTTP server with error route" << reset << endl;
    server.on_error = [](shared_ptr<http_server::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
        // do something
    };

    cout << bold << underline << "Start HTTP server on a thread" << reset << endl;
    thread server_thread([&server]() {
        server.start();
    });
    this_thread::sleep_for(chrono::seconds(1));

    cout << bold << on_yellow << "Simple HTTP Client" << reset << endl;
    http_client client("localhost:8080");
    string json_string = "{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";

    cout << bold << underline << "Request on the server we just created" << reset << endl;
    try {
        auto r1 = client.request("GET", "/match/123");
        cout << r1->content.rdbuf() << endl; // Alternatively, use the convenience function r1->content.string()

        auto r2 = client.request("GET", "/info");
        cout << r2->content.rdbuf() << endl;
    }
    catch(const SimpleWeb::system_error &e) {
        cerr << "Client request error: " << e.what() << endl;
    }

    cout << bold << underline << "Asynchronous request on the server we just created" << reset << endl;
    client.request("GET", "/info", [](shared_ptr<http_client::Response> response, const SimpleWeb::error_code &ec) {
        if(!ec)
            cout << response->content.rdbuf() << endl;
    });
    client.io_service->run();

    server_thread.join();

    return 0;
}

