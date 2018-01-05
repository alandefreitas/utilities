#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

#include "utils.h"

using namespace std;
using namespace utl;

int main()
{
    cout << bold << on_yellow << "Coloured Terminal" << reset << endl;

    cout << bold << underline << "Coloured Messages" << reset << endl;
    {
        cout << grey    << "grey message"    << reset << endl;
        cout << red     << "red message"     << reset << endl;
        cout << green   << "green message"   << reset << endl;
        cout << yellow  << "yellow message"  << reset << endl;
        cout << blue    << "blue message"    << reset << endl;
        cout << magenta << "magenta message" << reset << endl;
        cout << cyan    << "cyan message"    << reset << endl;
        cout << white   << "white message"   << reset << endl;
        cout << "default message" << endl;
        cout << endl;
    }

    cout << bold << underline << "Coloured Backgrounds" << reset << endl;
    {
        cout << on_grey << "message on grey" << reset << endl;
        cout << on_red << "message on red" << reset << endl;
        cout << on_green << "message on green" << reset << endl;
        cout << on_yellow << "message on yellow" << reset << endl;
        cout << on_blue << "message on blue" << reset << endl;
        cout << on_magenta << "message on magenta" << reset << endl;
        cout << on_cyan << "message on cyan" << reset << endl;
        cout << on_white << "message on white" << reset << endl;
        cout << red  << on_white  << "red on white"   << reset << endl;
        cout << blue << on_yellow << "blue on yellow" << reset << endl;
        cout << "default message" << endl;
        cout << endl;
    }

    cout << bold << underline << "Text attributes" << reset << endl;
    {
        cout << bold      << red  << "bold red message"  << reset << endl;
        cout << dark      << blue << "dark blue message" << reset << endl;
        cout << underline << "underlined message" << reset << endl;
        cout << blink     << "blinked message"    << reset << endl;
        cout << reversed   << "reversed message"   << reset << endl;
        cout << concealed << "concealed message"  << reset << endl;
        cout << "default message"    << endl;
    }

    cout << bold << underline << "Colored streams" << reset << endl;
    {
        stringstream ss;
        ss << grey << "This would be grey in the terminal";
        cout << "Grey stream: " << ss.str() << endl;
    }

    cout << bold << on_yellow << "Streaming containers" << reset << endl;

    cout << bold << underline << "Ordered Containers, Unordered Containers, and Containers of Containers" << reset << endl;
    {
        vector<double> x = {4.5, 7.3, 8.4, 4.5};
        cout << on_cyan << x << reset << endl;
        map<string,double> x2 = {{"PI",3.14}, {"NULL",0.0}, {"2^10",1024.00}};
        cout << on_grey << white << x2 << reset << endl;
        vector<vector<double>> x3 = {{4.5, 7.3, 8.4, 4.5},{4.5, 7.3, 8.4, 4.5},{4.5, 7.3, 8.4, 4.5}};
        cout << on_green << magenta << x3 << reset << endl;
    }

    cout << bold << on_yellow << "Pretty Tables" << reset << endl;

    cout << bold << underline << "Table with separators, formatting, and dynamic rows" << reset << endl;
    {
        utl::table t;
        // add data
        t.add_row({"", "Sex", "Age"});
        t.add("Moses");
        t.add("Male");
        t.add("4456");
        t.end_of_row();
        t.add_row({"Jesus", "Male", "2016"}).add_row({"Debora", "Female", "3001"});
        t.add_row({{"Moses", "Male",   "4556"},
                   {"Maria", "F__a_e", "323"}});
        vector<string> strs = {"Bob", "Male", "25"};
        t.add_row(strs);

        cout << t << endl;

        cout << bold << underline << "Coloring the table" << reset << endl;
        // settings
        t.min_width(10).text_color(utl::color::none)
         .text_background(utl::color::none)
         .bold(false)
         .underline(false)
         .corner_separator('+')
         .horizontal_separator('-')
         .vertical_separator('|')
         .border_bold(true)
         .border_underline(false)
         .border_color(utl::color::black)
         .border_background(utl::color::grey)
         .padding(1)
         .border_size(2)
         .border_height(1);

        t[0].underline(false).bold(true).text_background(utl::color::green);

        t[0][0].text_background(utl::color::grey);

        for (int i = 0; i < t.row_count(); ++i) {
            t[i][0].bold(true);
        }

        int oldest_pos = 4;
        t[oldest_pos][2].text_color(utl::color::red);
        int youngest_pos = 6;
        t[youngest_pos][2].text_color(utl::color::green).bold(true);
        int data_error_pos = 5;
        t[data_error_pos][1].text_background(utl::color::red).text_color(utl::color::yellow).underline(true);

        t.set_alignment(0, utl::alignment::right);
        t.set_alignment(1, utl::alignment::center);
        t.set_alignment(2, utl::alignment::center);

        // print
        cout << t << endl;
    }

    cout << bold << on_yellow << "Logging" << reset << endl;
    {
        cout << bold << underline << "Logging in the lowest level (DEBUG)" << reset << endl;
        utl::default_log_level::default_level = utl::log_level::debug;
        utl::log::info << "Information on the program..." << endl;
        using log = utl::log;
        log::critical << "Really serious problem!" << endl;
        log::debug << "This won't show up" << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::info << "Some normal information on what's happening" << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::warning << "This is something you might want to put in your todo list!" << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::error << "Ooooops... There's an error in your code." << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::critical << "THERE IS A SERIOUS ERROR IN YOU CODE." << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
        log::debug << "Details..." << endl;
    }

    cout << bold << on_yellow << "Progress bar" << reset << endl;
    {
        int goal = 3000000;
        int progress_resolution = 20;

        vector<double> v(goal);
        for (auto &&x : v) {
            x = utl::rand(0.00,100.00);
        }
        vector<double> v2(goal);

        utl::progress_bar p(goal,progress_resolution);
        cout << p.bar() << endl;
        for (int i = 0; i < goal; ++i) {
            cout << p.star(i);
            // do something that takes time here
            v2[i] = pow(v[i],2);
        }
        cout << endl;
        double sum = 0;
        for (auto &&item : v2) {
            sum+=item;
        }
        cout << sum << endl;
    }

    cout << on_yellow << bold << underline << "Streaming to containers" << reset << endl;

    cout << bold << underline << "Using an array as a device with iostreams::array_sink" << reset << endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        stream<array_sink> os{sink};
        os << "WoRd" << flush;
        cout.write(buffer, 5);
        cout << endl;
    }

    cout << bold << underline << "Using an array as a device with iostreams::array_source" << reset << endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        stream<array_sink> os{sink};
        os << "WoRd" << endl;

        array_source source{buffer};
        stream<array_source> is{source};
        string s;
        is >> s;
        cout << s << '\n';
    }

    cout << bold << underline << "Using a vector as a device with iostreams::back_insert_device" << reset << endl;
    {
        vector<char> v;
        back_insert_device<vector<char>> sink{v};
        stream<back_insert_device<vector<char>>> os{sink};
        os << "WoRd" << endl;

        array_source source{v.data(), v.size()};
        stream<array_source> is{source};
        string s;
        is >> s;
        cout << s << '\n';
    }

    cout << bold << underline << "Using a file as a device with iostreams::file_source" << reset << endl;
    {
        file_source f{"main.cpp"};
        if (f.is_open())
        {
            stream<file_source> is{f};
            cout << is.rdbuf() << '\n';
            f.close();
        }
    }

    cout << on_yellow << bold << underline << "Streams with filters" << reset << endl;

    cout << bold << underline << "Using iostreams::regex_filter" << reset << endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        filtering_ostream os;
        os.push(regex_filter{boost_regex{"Bo+st"}, "C++"});
        os.push(sink);
        os << "WoRd" << flush;
        os.pop();
        cout.write(buffer, 3);
        cout << endl;
    }

    cout << bold << underline << "Accessing filters in iostreams::filtering_ostream" << reset << endl;
    {
        char buffer[16];
        array_sink sink{buffer};
        filtering_ostream os;
        os.push(counter{});
        os.push(sink);
        os << "WoRd" << flush;
        os.pop();
        counter *c = os.component<counter>(0);
        cout << c->characters() << '\n';
        cout << c->lines() << '\n';
    }

    cout << on_yellow << bold << underline << "Streaming to/from the filesystem" << reset << endl;

    {
        cout << bold << underline << "Path Properties" << reset << endl;
        string project_path = PROJECTFOLDER;
        filesystem::path p{project_path};
        p /= "examples/stream_utils.cpp";

        // get path string properties
        cout << endl;
        cout << underline << "p: " << reset << p << endl;
        cout << underline << "p.root_name(): " << reset << p.root_name() << endl;
        cout << underline << "p.root_directory(): " << reset << p.root_directory() << endl;
        cout << underline << "p.root_path(): " << reset << p.root_path() << endl;
        cout << underline << "p.relative_path(): " << reset << p.relative_path() << endl;
        cout << underline << "p.parent_path(): " << reset << p.parent_path() << endl;
        cout << underline << "p.parent_path().parent_path(): " << reset << p.parent_path().parent_path() << endl;
        cout << underline << "p.parent_path().parent_path() [3]: " << reset << p.parent_path().parent_path() << endl;
        cout << underline << "p.parent_path().parent_path() [4]: " << reset << p.parent_path().parent_path().parent_path() << endl;
        cout << underline << "p.parent_path().parent_path() [5]: " << reset << p.parent_path().parent_path().parent_path().parent_path() << endl;
        cout << underline << "p.parent_path().parent_path() [6]: " << reset << p.parent_path().parent_path().parent_path().parent_path().parent_path() << endl;
        cout << underline << "p.parent_path().parent_path() [7]: " << reset << p.parent_path().parent_path().parent_path().parent_path().parent_path().parent_path() << endl;
        cout << underline << "p.parent_path().parent_path() [8]: " << p.parent_path().parent_path().parent_path().parent_path().parent_path().parent_path().parent_path() << endl;
        cout << "p.filename(): " << p.filename() << endl;
        cout << "p.stem(): " << p.stem() << endl;
        cout << "p.extension(): " << p.extension() << endl;

        cout << bold << underline << "Iterate Path Items" << reset << endl;
        for (const filesystem::path &pp : p) {
            cout << pp << endl;
        }

        cout << bold << underline << "Get status of file in the path" << reset << endl;
        filesystem::file_status s = status(p);
        cout << boolalpha << exists(s) << endl;
        if (exists(s)) {
            cout << boolalpha << is_directory(s) << endl;
            cout << boolalpha << is_regular_file(s) << endl;
            cout << boolalpha << is_symlink(s) << endl;

        }

        cout << bold << underline << "Get file size" << reset << endl;
        boost::system::error_code ec;
        uintmax_t filesize = file_size(p, ec);
        if (!ec) {
            cout << filesize << endl;
        } else {
            cout << ec << endl;
        }

        cout << bold << underline << "Get file properties" << reset << endl;
        try {
            time_t t = last_write_time(p);
            cout << ctime(&t) << endl;
        }
        catch (filesystem::filesystem_error &e) {
            cerr << e.what() << endl;
        }

        cout << bold << underline << "System Space" << reset << endl;
        try {
            filesystem::space_info s = space(p);
            cout << s.capacity << endl;
            cout << s.free << endl;
            cout << s.available << endl;
        }
        catch (filesystem::filesystem_error &e) {
            cerr << e.what() << endl;
        }

        cout << bold << underline << "Path where executable is running" << reset << endl;
        filesystem::path cur{filesystem::current_path()};
        cur /= "resources";
        cout << "Current path is -> " << cur << endl;

        cout << bold << underline << "Creating directories" << reset << endl;
        try {
            cout << bold << underline << "Try to create the directory on the path" << reset << endl;
            if (create_directory(cur)) {
                cout << "We can create directory" << endl;
                // rename what we created
                rename(cur, filesystem::absolute("latex_resources"), ec);
                if (!ec) {
                    cout << cur << endl;
                } else {
                    cout << ec << endl;
                }
                filesystem::remove(filesystem::absolute("latex_resources"));
                // Additional functions such as create_symlink() to create symbolic links or
                // copy_file() and
                // copy_directory() to copy files and directories are available as well.
            } else {
                cout << "We couldn't create directory" << cur << endl;
            }
        }
        catch (filesystem::filesystem_error &e) {
            cerr << e.what() << endl;
        }

        cout << bold << underline << "Find a path based on a file name or path section" << reset << endl;
        try {
            cout << filesystem::absolute("Make") << endl;
        }
        catch (filesystem::filesystem_error &e) {
            cerr << e.what() << endl;
        }

        cout << bold << underline << "Iterate files" << reset << endl;
        p = filesystem::path{project_path};
        p /= "examples";
        {
            filesystem::directory_iterator it{p};
            while (it != filesystem::directory_iterator{}) {
                cout << *(it++) << '\n';
            }
        }

        cout << bold << underline << "Recursively Iterate files" << reset << endl;
        {
            filesystem::recursive_directory_iterator it{p};
            while (it != filesystem::recursive_directory_iterator{}) {
                cout << *(it++) << '\n';
            }
        }

        cout << bold << underline << "File stream" << reset << endl;
        p = filesystem::path{"main.tex"};
        filesystem::ofstream ofs{p};
        ofs << "Hello, world!\n";

    }

    cout << on_yellow << bold << underline << "Plotting results" << reset << endl;
    cout << bold << underline << "GnuPlot" << reset << endl;
    {
        utl::plot(vector<double>({0,1,2,3,4,6,20}),vector<double>({2,3,4,5,6,7,100}));
        utl::plot(vector<double>({0,1,2,3,4,6.5,3.2,5.4}));
    }

    return 0;
}
