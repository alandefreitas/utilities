//
// Created by Alan de Freitas on 13/09/17.
//

#ifndef ROW_H
#define ROW_H

# include <stdexcept>
# include <string>
# include <vector>
# include <list>
# include <sstream>
#include "termcolor/termcolor.hpp"
#include "centered.h"
#include "error.h"
#include "enums.h"

namespace utl {
    class cell
            : public std::string {
        typedef cell self;
        public:
            cell(std::string s) : std::string(s) {}

            cell(const char* s) : std::string(s) {}

            cell() : std::string() {}

            ////////////////////////////////////////////////
            //                 SETTERS                    //
            ////////////////////////////////////////////////
            // set aligment of column i
            self &alignment(alignment alignment_) {
                _alignment = alignment_;
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

            ////////////////////////////////////////////////
            //                 GETTERS                    //
            ////////////////////////////////////////////////

            // text properties
            enum alignment alignment() const {
                return _alignment;
            }

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
            };

        private:
            ////////////////////////////////////////////////
            //                 MEMBERS                    //
            ////////////////////////////////////////////////
            enum alignment _alignment{alignment::none};
            bool bold_{false};
            bool underline_{false};
            color text_color_{color::none};
            color text_background_{color::none};

    };

    class row {
        typedef row self;
        public:
            row(const std::vector<std::string> &);

            row(size_t cells = 0);

            ////////////////////////////////////////////////
            //                 SETTERS                    //
            ////////////////////////////////////////////////

            // set aligment of column i
            self &alignment(alignment alignment_) {
                _alignment = alignment_;
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

            template<typename T>
            const T get_value(unsigned int pos) const {
                if (pos < _values.size()) {
                    T res;
                    std::stringstream ss;
                    ss << _values[pos];
                    ss >> res;
                    return res;
                }
                throw error("can't return this value (doesn't exist)");
            }

            void push_back(const std::string &);

            void assign(size_t n, std::string v) { _values.assign(n, v); }

            bool set(const std::string &, const std::string &);

            ////////////////////////////////////////////////
            //                 GETTERS                    //
            ////////////////////////////////////////////////

            // text properties
            enum alignment alignment() const {
                return _alignment;
            }

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

            unsigned int size(void) const;

            ////////////////////////////////////////////////
            //                OPERATORS                   //
            ////////////////////////////////////////////////

            const cell operator[](unsigned int) const;

            const std::string operator[](const std::string &valueName) const;

            cell &operator[](unsigned int cell_number){
                return _values.at(cell_number);
            };

            friend std::ostream &operator<<(std::ostream &os, const row &row__);

            friend std::ofstream &operator<<(std::ofstream &os, const row &row__);

        private:
            ////////////////////////////////////////////////
            //                 MEMBERS                    //
            ////////////////////////////////////////////////
            std::vector<std::string> _header;
            std::vector<cell> _values;

            enum alignment _alignment{alignment::none};
            bool bold_{false};
            bool underline_{false};
            color text_color_{color::none};
            color text_background_{color::none};
    };

    inline row::row(const std::vector<std::string> &header)
            : _header(header) {}

    inline row::row(size_t n)
            : _values(n) {}


    inline unsigned int row::size(void) const {
        return _values.size();
    }

    inline void row::push_back(const std::string &value) {
        _values.push_back(value);
    }

    inline bool row::set(const std::string &key, const std::string &value) {
        std::vector<std::string>::const_iterator it;
        int pos = 0;

        for (it = _header.begin(); it != _header.end(); it++) {
            if (key == *it) {
                _values[pos] = value;
                return true;
            }
            pos++;
        }
        return false;
    }

    inline const cell row::operator[](unsigned int valuePosition) const {
        if (valuePosition < _values.size()) {
            return _values[valuePosition];
        }
        throw error("can't return this value (doesn't exist)");
    }

    inline const std::string row::operator[](const std::string &key) const {
        std::vector<std::string>::const_iterator it;
        int pos = 0;

        for (it = _header.begin(); it != _header.end(); it++) {
            if (key == *it) {
                return _values[pos];
            }
            pos++;
        }

        throw error("can't return this value (doesn't exist)");
    }

    inline std::ostream &operator<<(std::ostream &os, const row &row__) {
        for (unsigned int i = 0; i != row__._values.size(); i++) {
            os << row__._values[i] << " | ";
        }

        return os;
    }

    inline std::ofstream &operator<<(std::ofstream &os, const row &row__) {
        for (unsigned int i = 0; i != row__._values.size(); i++) {
            os << row__._values[i];
            if (i < row__._values.size() - 1) {
                os << ",";
            }
        }
        return os;
    }
}

#endif //MARKDOWN_READER_ROW_H
