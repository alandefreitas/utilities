#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <vector>
#include <locale>
#include <cmath>
#include <chrono>

#include "utils.h"

using namespace std;
using namespace utl;

int main()
{
    cout << bold << on_yellow << "Timers" << reset << endl;

    cout << bold << on_yellow << "Measuring time" << reset << endl;
    {
        cpu_timer timer;
        for (int i = 0; i < 1000000; ++i) {
            pow(1.234, i);
        }
        cout << "timer.format(): " << timer.format() << '\n';
    }

    cout << bold << underline << "Stopping and resuming timers" << reset
         << endl;
    {
        cpu_timer timer;
        for (int i = 0; i < 1000000; ++i) {
            pow(1.234, i);
        }
        cout << "timer.format(): " << timer.format() << '\n';
        timer.stop();
        for (int i = 0; i < 1000000; ++i) {
            pow(1.234, i);
        }
        cout << "timer.format(): " << timer.format() << '\n';
        timer.resume();
        for (int i = 0; i < 1000000; ++i) {
            pow(1.234, i);
        }
        cout << "timer.format(): " << timer.format() << '\n';
    }

    cout << bold << underline << "Getting wall and CPU time as a tuple" << reset
         << endl;
    {
        cpu_timer timer;

        for (int i = 0; i < 1000000; ++i) {
            pow(1.234, i);
        }

        cpu_times times = timer.elapsed();
        cout << "times.wall: " << times.wall << '\n';
        cout << "times.user: " << times.user << '\n';
        cout << "times.system: " << times.system << '\n';
    }

    cout << bold << underline << "Measuring times automatically with timer::auto_cpu_timer" << reset << endl;
    {
        auto_cpu_timer timer;

        for (int i = 0; i < 1000000; ++i) {
            pow(1.234, i);
        }
    }

    cout << bold << on_yellow << "Clocks, Timepoints, and Durations" << reset << endl;

    cout << bold << underline << "Clocks" << reset << endl;
    {
        cout << "System time: " << system_clock::now() << '\n';
        cout << "Monotonic time: " << steady_clock::now() << '\n';
        cout << "Precise time: " << high_resolution_clock::now() << '\n';
        cout << "CPU time this process has been running: " << process_real_cpu_clock::now() << '\n';
        cout << "CPU time this process spent in user space: " << process_user_cpu_clock::now() << '\n';
        cout << "CPU time this process spent in kernel space: " << process_system_cpu_clock::now() << '\n';
        cout << "CPU time spent in this process, user, and kernel space: " << process_cpu_clock::now() << '\n';
        cout << "Time used by this thread: " << thread_clock::now() << '\n';
    }

    cout << bold << underline << "Durations" << reset << endl;
    {
        cpu_clock::time_point p = cpu_clock::now();
        cout << p << '\n';
        cout << p - nanoseconds{1} << '\n';
        cout << p + milliseconds{1} << '\n';
        cout << p + seconds{1} << '\n';
        cout << p + minutes{1} << '\n';
        cout << p + hours{1} << '\n';
        cout << "Minutes in the cpu clocks: " << time_point_cast<minutes>(p) << '\n';
        cout << "Seconds in the cpu clocks: " << time_point_cast<seconds>(p) << '\n';
        minutes m{1};
        seconds s{35};
        cout << m + s << '\n';
        cout << duration_cast<minutes>(m + s) << '\n';
    }

    cout << bold << underline << "Rounding durations" << reset << endl;
    {
        cout << floor<minutes>(minutes{1} + seconds{45}) << '\n';
        cout << round<minutes>(minutes{1} + seconds{15}) << '\n';
        cout << ceil<minutes>(minutes{1} + seconds{15}) << '\n';
    }

    cout << bold << on_yellow << "Streaming time" << reset << endl;
    cout << bold << underline << "Stream manipulators for user-defined output" << reset << endl;
    {
        cout << symbol_format << minutes{10} << '\n';
        cout << symbol_format << minutes{1} + seconds{45} << '\n';
        cout << time_fmt(timezones::local, "%H:%M:%S") << system_clock::now() << '\n';
    }

    cout << on_yellow << bold << underline << "Calendar Dates and Time" << reset << endl;
    cout << bold << underline << "Creating a date with gregorian date" << reset << endl;
    {
        gregorian::date d{2014, 1, 31};
        cout << "d.year(): " << d.year() << '\n';
        cout << "d.month(): " << d.month() << '\n';
        cout << "d.day(): " << d.day() << '\n';
        cout << "d.day_of_week(): " << d.day_of_week() << '\n';
        cout << "d.end_of_month(): " << d.end_of_month() << '\n';
    }

    cout << bold << underline << "Getting a date from a clock or a string" << reset << endl;
    {
        gregorian::date d = gregorian::day_clock::universal_day();
        cout << "d.year(): " << d.year() << '\n';
        cout << "d.month(): " << d.month() << '\n';
        cout << "d.day(): " << d.day() << '\n';

        d = gregorian::date_from_iso_string("20140131");
        cout << "d.year(): " << d.year() << '\n';
        cout << "d.month(): " << d.month() << '\n';
        cout << "d.day(): " << d.day() << '\n';
    }

    cout << bold << underline << "Using gregorian::date_duration" << reset << endl;
    {
        gregorian::date d1{2014, 1, 31};
        gregorian::date d2{2014, 2, 28};
        gregorian::date_duration dd = d2 - d1;
        cout << "dd.days(): " << dd.days() << '\n';
    }

    cout << bold << underline << "Specialized durations" << reset << endl;
    {
        gregorian::date_duration dd{4};
        cout << "dd.days(): " << dd.days() << '\n';
        gregorian::weeks ws{4};
        cout << "ws.days(): " << ws.days() << '\n';
        gregorian::months ms{4};
        cout << "ms.number_of_months(): " << ms.number_of_months() << '\n';
        gregorian::years ys{4};
        cout << "ys.number_of_years(): " << ys.number_of_years() << '\n';
    }

    cout << bold << underline << "Processing specialized durations" << reset << endl;
    {
        gregorian::date d{2014, 1, 31};
        gregorian::months ms{1};
        gregorian::date d2 = d + ms;
        cout << "d2: " << d2 << '\n';
        gregorian::date d3 = d2 - ms;
        cout << "d3: " << d3 << '\n';
    }

    cout << bold << underline << "Surprises when processing specialized durations" << reset << endl;
    {
        gregorian::date d{2014, 1, 30};
        gregorian::months ms{1};
        gregorian::date d2 = d + ms;
        cout << "d2: " << d2 << '\n';
        gregorian::date d3 = d2 - ms;
        cout << "d3: " << d3 << '\n';
    }

    cout << bold << underline << "Using gregorian::date_period" << reset << endl;
    {
        gregorian::date d1{2014, 1, 1};
        gregorian::date d2{2014, 2, 28};
        gregorian::date_period dp{d1, d2};
        gregorian::date_duration dd = dp.length();
        cout << "dd.days(): " << dd.days() << '\n';
    }

    cout << bold << underline << "Testing whether a period contains dates" << reset << endl;
    {
        gregorian::date d1{2014, 1, 1};
        gregorian::date d2{2014, 2, 28};
        gregorian::date_period dp{d1, d2};
        cout.setf(ios::boolalpha);
        cout << "dp.contains(d1): " << dp.contains(d1) << '\n';
        cout << "dp.contains(d2): " << dp.contains(d2) << '\n';
    }

    cout << bold << underline << "Iterating over dates" << reset << endl;
    {
        gregorian::date d{2014, 5, 12};
        gregorian::day_iterator it{d};
        cout << "*++it: " << *++it << '\n';
        cout << "date_time::next_weekday(*it,gregorian::greg_weekday(date_time::Friday)): "
                  << date_time::next_weekday(*it, gregorian::greg_weekday(date_time::Friday)) << '\n';
    }

    cout << on_yellow << bold << underline << "Location-independent Times" << reset << endl;

    cout << bold << underline << "Using ptime" << reset << endl;
    {
        ptime pt{gregorian::date{2014, 5, 12}, time_duration{12, 0, 0}};
        gregorian::date d = pt.date();
        cout << "d: " << d << '\n';
        time_duration td = pt.time_of_day();
        cout << "td: " << td << '\n';
    }

    cout << bold << underline << "Creating a timepoint with a clock or a string" << reset << endl;
    {
        ptime pt = second_clock::universal_time();
        cout << "pt.date(): " << pt.date() << '\n';
        cout << "pt.time_of_day(): " << pt.time_of_day() << '\n';

        pt = from_iso_string("20140512T120000");
        cout << "pt.date(): " << pt.date() << '\n';
        cout << "pt.time_of_day(): " << pt.time_of_day() << '\n';
    }

    cout << bold << underline << "Using time_duration" << reset << endl;
    {
        time_duration td{16, 30, 0};
        cout << "td.hours(): " << td.hours() << '\n';
        cout << "td.minutes(): " << td.minutes() << '\n';
        cout << "td.seconds(): " << td.seconds() << '\n';
        cout << "td.total_seconds(): " << td.total_seconds() << '\n';
    }

    cout << bold << underline << "Processing timepoints" << reset << endl;
    {
        ptime pt1{gregorian::date{2014, 5, 12}, time_duration{12, 0, 0}};
        ptime pt2{gregorian::date{2014, 5, 12}, time_duration{18, 30, 0}};
        time_duration td = pt2 - pt1;
        cout << "td.hours(): " << td.hours() << '\n';
        cout << "td.minutes(): " << td.minutes() << '\n';
        cout << "td.seconds(): " << td.seconds() << '\n';
    }

    cout << bold << underline << "Processing time durations" << reset << endl;
    {
        ptime pt1{gregorian::date{2014, 5, 12}, time_duration{12, 0, 0}};
        time_duration td{6, 30, 0};
        ptime pt2 = pt1 + td;
        cout << "pt2.time_of_day(): " << pt2.time_of_day() << '\n';
    }

    cout << bold << underline << "Using time_period" << reset << endl;
    {
        ptime pt1{gregorian::date{2014, 5, 12}, time_duration{12, 0, 0}};
        ptime pt2{gregorian::date{2014, 5, 12}, time_duration{18, 30, 0}};
        time_period tp{pt1, pt2};
        cout.setf(ios::boolalpha);
        cout << "tp.contains(pt1): " << tp.contains(pt1) << '\n';
        cout << "tp.contains(pt2): " << tp.contains(pt2) << '\n';
    }

    cout << bold << underline << "Iterating over points in time" << reset << endl;
    {
        ptime pt{gregorian::date{2014, 5, 12}, time_duration{12, 0, 0}};
        time_iterator it{pt, time_duration{6, 30, 0}};
        cout << "*++it: " << *++it << '\n';
        cout << "*++it: " << *++it << '\n';
    }

    cout << on_yellow << bold << underline << "Location-dependent Times" << reset << endl;

    cout << bold << underline << "Using local_time::local_date_time" << reset << endl;
    {
        local_time::time_zone_ptr tz{new local_time::posix_time_zone{"CET+1"}};
        ptime pt{gregorian::date{2014, 5, 12}, time_duration{12, 0, 0}};
        local_time::local_date_time dt{pt, tz};
        cout << "dt.utc_time(): " << dt.utc_time() << '\n';
        cout << "dt: " << dt << '\n';
        cout << "dt.local_time(): " << dt.local_time() << '\n';
        cout << "dt.zone_name(): " << dt.zone_name() << '\n';
    }

    cout << bold << underline << "Location-dependent points in time and different time zones" << reset << endl;
    {
        local_time::time_zone_ptr tz{new local_time::posix_time_zone{"CET+1"}};

        ptime pt{gregorian::date{2014, 5, 12}, time_duration{12, 0, 0}};
        local_time::local_date_time dt{pt, tz};
        cout << "dt.local_time(): " << dt.local_time() << '\n';

        local_time::time_zone_ptr tz2{new local_time::posix_time_zone{"EET+2"}};
        cout << "dt.local_time_in(tz2).local_time(): " << dt.local_time_in(tz2).local_time() << '\n';
    }

    cout << bold << underline << "Using local_time::local_time_period" << reset << endl;
    {
        local_time::time_zone_ptr tz{new local_time::posix_time_zone{"CET+0"}};

        ptime pt1{gregorian::date{2014, 12, 5}, time_duration{12, 0, 0}};
        local_time::local_date_time dt1{pt1, tz};

        ptime pt2{gregorian::date{2014, 12, 5}, time_duration{18, 0, 0}};
        local_time::local_date_time dt2{pt2, tz};

        local_time::local_time_period tp{dt1, dt2};

        cout.setf(ios::boolalpha);
        cout << "tp.contains(dt1): " << tp.contains(dt1) << '\n';
        cout << "tp.contains(dt2): " << tp.contains(dt2) << '\n';
    }

    cout << on_yellow << bold << underline << "Formatted Input and Output" << reset << endl;

    cout << bold << underline << "A user-defined format for a date" << reset << endl;
    {
        gregorian::date d{2014, 5, 12};
        gregorian::date_facet *df = new gregorian::date_facet{"%A, %d %B %Y"};
        cout.imbue(locale{cout.getloc(), df});
        cout << "d: " << d << '\n';
    }

    cout << bold << underline << "Changing names of weekdays and months" << reset << endl;
    {
        // locale::global(locale{"de_DE"});
        // locale::global(locale{"German"}); // on windows
        string months[12]{"Januar", "Februar", "M\xe4rz", "April",
                               "Mai", "Juni", "Juli", "August", "September", "Oktober",
                               "November", "Dezember"};
        string weekdays[7]{"Sonntag", "Montag", "Dienstag",
                                "Mittwoch", "Donnerstag", "Freitag", "Samstag"};
        gregorian::date d{2014, 5, 12};
        gregorian::date_facet *df = new gregorian::date_facet{"%A, %d. %B %Y"};
        df->long_month_names(vector<string>{months, months + 12});
        df->long_weekday_names(vector<string>{weekdays,
                                                        weekdays + 7});
        cout.imbue(locale{cout.getloc(), df});
        cout << d << '\n';
    }



    return 0;
}
