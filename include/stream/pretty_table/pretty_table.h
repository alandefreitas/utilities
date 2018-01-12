#ifndef TEXT_TABLE_H
#define TEXT_TABLE_H

#include <map>
#include <iomanip>
#include <vector>
#include <string>

#include <initializer_list>
#include <stdexcept>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include "termcolor/termcolor.hpp"

#include "centered.h"
#include "error.h"
#include "row.h"
#include "enums.h"

namespace utl {
    class table {
        public:
            typedef table self;

            ////////////////////////////////////////////////
            //               CONSTRUCTORS                 //
            ////////////////////////////////////////////////

            table() {}

            table(std::initializer_list<std::string> l) {
                add_row(l);
            }

            table(std::initializer_list<std::initializer_list<std::string>> l) {
                for (auto &&item : l) {
                    add_row(item);
                }
            }

            table(size_t rows_n, size_t cols_n) : _rows(rows_n,cols_n) {
            }

            table(const std::string &, char sep = ',', const datatype &type = file);

            ////////////////////////////////////////////////
            //                 SETTERS                    //
            ////////////////////////////////////////////////

            // set aligment of column i
            self &set_alignment(unsigned column_index, alignment alignment_) {
                _alignment[column_index] = alignment_;
                return *this;
            }

            // add element to current temporary row
            self &add(std::string const &content) {
                _current_temp_row.push_back(content);
                return *this;
            }

            // text/table properties
            self &horizontal_separator(char separator) {
                _horizontal = separator;
                return *this;
            }

            self &vertical_separator(char separator) {
                _vertical = separator;
                return *this;
            }

            self &corner_separator(char separator) {
                _corner = separator;
                return *this;
            }


            self &bold(unsigned bold__) {
                bold_ = bold__;
                return *this;
            }

            self &underline(unsigned underline__) {
                underline_ = underline__;
                return *this;
            }

            self &text_color(color color__) {
                text_color_ = color__;
                return *this;
            };

            self &text_background(color color__) {
                text_background_ = color__;
                return *this;
            };

            // border properties
            self &border_size(unsigned border_size__) {
                border_size_ = border_size__;
                return *this;
            }

            self &border_height(unsigned border_height__) {
                border_height_ = border_height__;
                return *this;
            }

            self &border_bold(unsigned border_bold__) {
                border_bold_ = border_bold__;
                return *this;
            }

            self &border_underline(unsigned border_underline__) {
                border_underline_ = border_underline__;
                return *this;
            }

            self &border_color(color color__) {
                border_color_ = color__;
                return *this;
            };

            self &border_background(color color__) {
                border_background_ = color__;
                return *this;
            };

            // cell properties
            self &padding(unsigned padding__) {
                padding_ = padding__;
                return *this;
            }

            self &min_width(unsigned _min_width__) {
                _min_width_ = _min_width__;
                return *this;
            }

            // add elements to temp row
            template<typename Iterator>
            self &add_row(Iterator begin, Iterator end) {
                for (auto i = begin; i != end; ++i) {
                    add(*i);
                }
                end_of_row();
                return *this;
            }

            // add elements to temp row
            template<typename Container>
            self &add_row(Container const &container) {
                add_row(container.begin(), container.end());
                return *this;
            }

            self &add_row(std::initializer_list<std::string> l) {
                add_row(l.begin(), l.end());
                return *this;
            }


            self &add_row(std::initializer_list<std::initializer_list<std::string>> l) {
                for (auto &&item : l) {
                    add_row(item);
                }
                return *this;
            }


            self &add_row(std::initializer_list<double> l) {
                for (auto i = l.begin(); i != l.end(); ++i) {
                    add(std::to_string(*i));
                }
                end_of_row();
                return *this;
            }

            self &add_row(std::initializer_list<int> l) {
                for (auto i = l.begin(); i != l.end(); ++i) {
                    add(std::to_string(*i));
                }
                end_of_row();
                return *this;
            }


            // push temp row to table
            self &end_of_row() {
                _rows.push_back(_current_temp_row);
                _current_temp_row.assign(0, "");
                return *this;
            }

            bool delete_row(unsigned int row);

            bool add_row(unsigned int pos, const std::vector<std::string> &);

            void sync(void) const;

            row &operator[](unsigned int row);

            ////////////////////////////////////////////////
            //                 GETTERS                    //
            ////////////////////////////////////////////////

            row &get_row(unsigned int);

            unsigned int row_count(void) const;

            unsigned int column_count(void) const;

            std::vector<std::string> get_header(void) const;

            const std::string get_header_element(unsigned int pos) const;

            const std::string &get_filename(void) const;

            // get vector with all rows
            std::vector<row> const &rows() const {
                return _rows;
            }

            // get aligment of column i
            alignment get_alignment(unsigned i) const { return _alignment[i]; }

            // get vertical separator
            char vertical() const { return _vertical; }

            // get horizontal separator
            char horizontal() const { return _horizontal; }

            // get width of a column
            int width(unsigned i) const { return _width[i]; }

            // text properties
            bool bold() const {
                return bold_;
            }

            bool underline() const {
                return underline_;
            }

            color text_color() const {
                return text_color_;
            }

            color text_backgroung() const {
                return text_background_;
            }

            // border properties
            unsigned border_size() const {
                return border_size_;
            }

            unsigned border_height() const {
                return border_height_;
            }

            bool border_bold() const {
                return border_bold_;
            }

            bool border_underline() const {
                return border_underline_;
            }

            color border_color() const {
                return border_color_;
            }

            color border_backgroung() const {
                return border_background_;
            }

            // cell properties
            unsigned padding() const {
                return padding_;
            }

            unsigned min_width() const {
                return _min_width_;
            }

            // return number of columns
            unsigned columns() const {
                return _rows[0].size();
            }

            // organize table for impression
            void setup() {
                determine_widths();
                setup_alignment();
            }

            // get string representing the table border
            std::string border() const;

            ////////////////////////////////////////////////
            //                OPERATORS                   //
            ////////////////////////////////////////////////
            friend std::ostream &operator<<(std::ostream &, table &table);

        protected:
            void parse_header(void);

            void parse_content(void);

        private:
            ////////////////////////////////////////////////
            //                 MEMBERS                    //
            ////////////////////////////////////////////////
            // separators
            char _horizontal{'-'};
            char _vertical{'|'};
            char _corner{'+'};

            // table
            row _current_temp_row;
            std::vector<row> _rows;

            // properties
            std::vector<unsigned> mutable _width;
            std::map<unsigned, alignment> mutable _alignment;

            bool bold_{false};
            bool underline_{false};
            color text_color_{color::none};
            color text_background_{color::none};

            unsigned border_size_{1};
            unsigned border_height_{1};
            bool border_bold_{false};
            bool border_underline_{false};
            color border_color_{color::none};
            color border_background_{color::none};

            unsigned padding_{0};
            unsigned _min_width_{5};

            // csv data
            std::string _file;
            const datatype _type{datatype::pure};
            const char _sep{','};
            std::vector<std::string> _original_file;
            std::vector<std::string> _header;

            ////////////////////////////////////////////////
            //            PRIVATE FUNCTIONS               //
            ////////////////////////////////////////////////
            // determine width of column i
            void determine_width(int i) const {
                _width.resize(columns());
                for (auto &row : _rows) {
                    _width[i] = std::max((int) _width[i], (int) row[i].size());
                }
            }

            // determine width of each column
            void determine_widths() const {
                for (unsigned i = 0; i < _rows[0].size(); ++i) {
                    determine_width(i);
                }
            }

            // setup each aligment
            void setup_alignment() const {
                for (unsigned i = 0; i < columns(); ++i) {
                    if (_alignment.find(i) == _alignment.end()) {
                        _alignment[i] = alignment::center;
                    }
                }
            }
    };

    // create string with the char c many times
    inline std::string repeat(unsigned times, char c) {
        std::string result;
        for (; times > 0; --times) {
            result += c;
        }
        return result;
    }

    inline std::string table::border() const {
        std::string result;
        result += repeat(border_size(), _corner);
        for (auto width = _width.begin(); width != _width.end(); ++width) {
            result += repeat(std::max(_min_width_, *width) + padding() * 2, _horizontal);
            result += repeat(border_size(), _corner);
        }
        return result;
    }

    inline std::ostream &stream_aligned_text(std::ostream &stream, table &table, alignment a, std::string text, int width) {
        switch (a) {
            case alignment::center:
                stream << std::setw(width) << centered(text);
                break;
            case alignment::left:
                stream << std::setw(width) << std::left << text;
                break;
            case alignment::right:
                stream << std::setw(width) << std::right << text;
                break;
            case alignment::none:
                break;
        }
        return stream;
    }

    inline std::ostream &
    stream_text_properties(std::ostream &stream, bool bold, bool underline, color color_, color background_) {
        if (bold) {
            stream << termcolor::bold;
        }
        if (underline) {
            stream << termcolor::underline;
        }
        if (color_ != color::none) {
            switch (color_) {
                case (color::blue):
                    stream << termcolor::blue;
                    break;
                case (color::cyan):
                    stream << termcolor::cyan;
                    break;
                case (color::green):
                    stream << termcolor::green;
                    break;
                case (color::black):
                    stream << termcolor::grey;
                    break;
                case (color::magenta):
                    stream << termcolor::magenta;
                    break;
                case (color::red):
                    stream << termcolor::red;
                    break;
                case (color::grey):
                    stream << termcolor::white;
                    break;
                case (color::yellow):
                    stream << termcolor::yellow;
                    break;
                case (color::none):
                    break;
            }
        }
        if (background_ != color::none) {
            switch (background_) {
                case (color::blue):
                    stream << termcolor::on_blue;
                    break;
                case (color::cyan):
                    stream << termcolor::on_cyan;
                    break;
                case (color::green):
                    stream << termcolor::on_green;
                    break;
                case (color::black):
                    stream << termcolor::on_grey;
                    break;
                case (color::magenta):
                    stream << termcolor::on_magenta;
                    break;
                case (color::red):
                    stream << termcolor::on_red;
                    break;
                case (color::grey):
                    stream << termcolor::on_white;
                    break;
                case (color::yellow):
                    stream << termcolor::on_yellow;
                    break;
                case (color::none):
                    break;
            }
        }
        return stream;
    }

    inline std::ostream &stream_table_line(std::ostream &stream, table &table, utl::row row) {
        stream_text_properties(stream, table.border_bold(), table.border_underline(), table.border_color(),
                               table.border_backgroung());
        for (int i = 0; i < table.border_size(); ++i) {
            stream << table.vertical();
        }
        stream << termcolor::reset;

        for (unsigned i = 0; i < row.size(); ++i) {
            stream_text_properties(stream,
                                   row[i].bold() ? row[i].bold() : (row.bold() ? row.bold() : table.bold()),
                                   row[i].underline() ? row[i].underline() : (row.underline() ? row.underline()
                                                                                    : table.underline()),
                                   row[i].text_color() != color::none ? row[i].text_color() : (row.text_color() == color::none
                                                                    ? table.text_color() : row.text_color()),
                                   row[i].text_backgroung() != color::none ? row[i].text_backgroung() : (row.text_backgroung() == color::none
                                                                    ? table.text_backgroung()
                                                                    : row.text_backgroung()));
            stream << repeat(table.padding(), ' ');
            stream_aligned_text(stream, table, table.get_alignment(i), row[i],
                                std::max((int) table.width(i), (int) table.min_width()));
            stream << repeat(table.padding(), ' ');
            stream << termcolor::reset;

            stream_text_properties(stream, table.border_bold(), table.border_underline(), table.border_color(),
                                   table.border_backgroung());
            for (int i = 0; i < table.border_size(); ++i) {
                stream << table.vertical();
            }
            stream << termcolor::reset;
        }
        stream << "\n";
        return stream;
    }

    inline std::ostream &stream_border_line(std::ostream &stream, table &table) {
        for (int i = 0; i < table.border_height(); ++i) {
            stream_text_properties(stream, table.border_bold(), table.border_underline(), table.border_color(),
                                   table.border_backgroung());
            stream << table.border();
            stream << termcolor::reset;
            stream << "\n";
        }
        return stream;
    }

    inline std::ostream &operator<<(std::ostream &stream, table &table) {
        table.setup();
        stream_border_line(stream, table);
        for (auto rowIterator = table.rows().begin(); rowIterator != table.rows().end(); ++rowIterator) {
            stream_table_line(stream, table, *rowIterator);
            stream_border_line(stream, table);
        }
        return stream;
    }

    inline table::table(const std::string &filename, char sep, const datatype &type)
            : _type(type), _sep(sep) {
        std::string line;
        if (type == file) {
            _file = filename;
            std::ifstream ifile(_file.c_str());
            if (ifile.is_open()) {
                while (ifile.good()) {
                    getline(ifile, line);
                    if (line != "") {
                        _original_file.push_back(line);
                    }
                }
                ifile.close();

                if (_original_file.size() == 0) {
                    throw error(std::string("No Data in ").append(_file));
                }

                parse_header();
                parse_content();
            } else {
                throw error(std::string("Failed to open ").append(_file));
            }
        } else {
            std::istringstream stream(filename);
            while (std::getline(stream, line)) {
                if (line != "") {
                    _original_file.push_back(line);
                }
            }
            if (_original_file.size() == 0) {
                throw error(std::string("No Data in pure content"));
            }

            parse_header();
            parse_content();
        }
    }

    inline void table::parse_header(void) {
        std::stringstream ss(_original_file[0]);
        std::string item;

        while (std::getline(ss, item, _sep)) {
            _header.push_back(item);
        }
    }

    inline void table::parse_content(void) {
        std::vector<std::string>::iterator it;

        it = _original_file.begin();
        it++; // skip header

        for (; it != _original_file.end(); it++) {
            bool quoted = false;
            int tokenStart = 0;
            unsigned int i = 0;

            row temp_row(_header);

            for (; i != it->length(); i++) {
                if (it->at(i) == '"') {
                    quoted = ((quoted) ? (false) : (true));
                } else if (it->at(i) == ',' && !quoted) {
                    temp_row.push_back(it->substr(tokenStart, i - tokenStart));
                    tokenStart = i + 1;
                }
            }

            //end
            temp_row.push_back(it->substr(tokenStart, it->length() - tokenStart));

            // if value(s) missing
            if (temp_row.size() != _header.size()) {
                throw error("corrupted data !");
            }
            _rows.push_back(temp_row);
        }
    }

    inline row &table::get_row(unsigned int row_number) {
        return _rows.at(row_number);
    }

    inline row &table::operator[](unsigned int row_number) {
        return table::get_row(row_number);
    }

    inline unsigned int table::row_count(void) const {
        return _rows.size();
    }

    inline unsigned int table::column_count(void) const {
        return _rows[0].size();
    }

    inline std::vector<std::string> table::get_header(void) const {
        return _header;
    }

    inline const std::string table::get_header_element(unsigned int pos) const {
        if (pos >= _header.size()) {
            throw error("can't return this header (doesn't exist)");
        }
        return _header[pos];
    }

    inline bool table::delete_row(unsigned int pos) {
        if (pos < _rows.size()) {
            _rows.erase(_rows.begin() + pos);
            return true;
        }
        return false;
    }

    inline bool table::add_row(unsigned int pos, const std::vector<std::string> &r) {
        row temp_row(_header);

        for (auto it = r.begin(); it != r.end(); it++) {
            temp_row.push_back(*it);
        }

        if (pos <= _rows.size()) {
            _rows.insert(_rows.begin() + pos, temp_row);
            return true;
        }
        return false;
    }

    inline void table::sync(void) const {
        if (_type == datatype::file) {
            std::ofstream f;
            f.open(_file, std::ios::out | std::ios::trunc);

            // header
            unsigned int i = 0;
            for (auto it = _header.begin(); it != _header.end(); it++) {
                f << *it;
                if (i < _header.size() - 1) {
                    f << ",";
                } else {
                    f << std::endl;
                }
                i++;
            }

            for (auto it = _rows.begin(); it != _rows.end(); it++) {
                f << *it << std::endl;
            }
            f.close();
        }
    }

    inline const std::string &table::get_filename(void) const {
        return _file;
    }

}

#endif