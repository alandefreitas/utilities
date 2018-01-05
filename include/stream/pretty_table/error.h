//
// Created by Alan de Freitas on 13/09/17.
//

#ifndef TEXT_TABLE_ERROR_H
#define TEXT_TABLE_ERROR_H

namespace utl {
    class error : public std::runtime_error
    {
        public:
            error(const std::string &msg):
                    std::runtime_error(std::string("CSVparser : ").append(msg))
            {
            }
    };
}


#endif //MARKDOWN_READER_ERROR_H
