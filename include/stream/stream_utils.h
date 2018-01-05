//
// Created by Alan de Freitas on 03/01/18.
//

#ifndef UTILITIES_STREAM_UTILS_H
#define UTILITIES_STREAM_UTILS_H

// External
#include "include/termcolor/termcolor.hpp"

#include "prettyprint.hpp"

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/file.hpp>
// ambiguous back_inserter
// #include <boost/iostreams/device/back_inserter.hpp>

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/iostreams/filter/counter.hpp>

#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

// Internal
#include "pretty_table/pretty_table.h"
#include "logging.h"
#include "progress_bar.h"
#include "plots.h"


namespace utl {
    using namespace termcolor;
    inline std::ostream& reversed(std::ostream& stream) {
        return termcolor::reverse(stream);
    }

    using namespace boost::iostreams;

    namespace filesystem = boost::filesystem;

    using boost_regex = boost::regex;
    namespace boost_regex_constants = boost::regex_constants;

    template<typename Container>
    class back_insert_device {
        public:
            typedef typename Container::value_type  char_type;
            typedef ::boost::iostreams::sink_tag    category;
            back_insert_device(Container& cnt) : container(&cnt) { }
            std::streamsize write(const char_type* s, std::streamsize n)
            {
                container->insert(container->end(), s, s + n);
                return n;
            }
        protected:
            Container* container;
    };

}



#endif //UTILITIES_STREAM_UTILS_H
