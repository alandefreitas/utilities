//
// Created by Alan de Freitas on 03/01/18.
//

#ifndef UTILITIES_TIME_UTILS_H
#define UTILITIES_TIME_UTILS_H

#include <chrono>

// External
#ifndef BOOST_CHRONO_VERSION
    #define BOOST_CHRONO_VERSION 2
#endif
#include <boost/chrono.hpp>
#include <boost/chrono/chrono_io.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

#include <boost/timer/timer.hpp>

namespace utl {
    // timers
    using boost::timer::cpu_timer;
    using boost::timer::cpu_times;
    using boost::timer::auto_cpu_timer;

    // clocks
    using system_clock = boost::chrono::system_clock;
    #ifdef BOOST_CHRONO_HAS_CLOCK_STEADY
        using steady_clock = boost::chrono::steady_clock;
    #else
        using steady_clock = std::chrono::steady_clock;
    #endif
    using high_resolution_clock = boost::chrono::high_resolution_clock;

    #ifdef BOOST_CHRONO_HAS_PROCESS_CLOCKS
        using process_real_cpu_clock = boost::chrono::process_real_cpu_clock;
        using process_user_cpu_clock = boost::chrono::process_user_cpu_clock;
        using process_system_cpu_clock = boost::chrono::process_system_cpu_clock;
        using process_cpu_clock = boost::chrono::process_cpu_clock;
    #else
        using process_real_cpu_clock = boost::chrono::high_resolution_clock;
        using process_user_cpu_clock = boost::chrono::high_resolution_clock;
        using process_system_cpu_clock = boost::chrono::high_resolution_clock;
        using process_cpu_clock = boost::chrono::high_resolution_clock;
    #endif
    using cpu_clock = process_real_cpu_clock;
    #ifdef BOOST_CHRONO_HAS_THREAD_CLOCK
        using thread_clock = boost::chrono::thread_clock;
    #else
        using thread_clock = boost::chrono::high_resolution_clock;
    #endif

    // Durations
    using boost::chrono::nanoseconds;
    using boost::chrono::milliseconds;
    using boost::chrono::microseconds;
    using boost::chrono::seconds;
    using boost::chrono::minutes;
    using boost::chrono::hours;

    using boost::chrono::time_point_cast;
    using boost::chrono::duration_cast;

    // Streaming time
    using boost::chrono::symbol_format;
    using boost::chrono::time_fmt;
    using timezones = boost::chrono::timezone;

    // Date types
    namespace gregorian = boost::gregorian;
    namespace local_time = boost::local_time;
    namespace posix_time = boost::posix_time;
    namespace date_time = boost::date_time;

    using ptime = posix_time::ptime;
    using second_clock = posix_time::second_clock;
    using time_duration = posix_time::time_duration;
    using time_period = posix_time::time_period;
    using time_iterator = posix_time::time_iterator;

    inline ptime from_iso_string(const std::string& s) {
        return date_time::parse_iso_time<ptime>(s, 'T');
    }


}

#endif //UTILITIES_TIME_UTILS_H
