//
// Created by Ilya Sysoi on 1/19/20.
//

#ifndef JSON_READEREXCEPTION_H
#define JSON_READEREXCEPTION_H

#include <exception>
#include <string>

class ReaderException : public std::exception {
public:
    explicit ReaderException(const char *message)
            : msg_(message) {}

    explicit ReaderException(const std::string &message)
            : msg_(message) {}

    virtual ~ReaderException() throw() {}

    virtual const char *what() const throw() {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};

#endif //JSON_READEREXCEPTION_H
