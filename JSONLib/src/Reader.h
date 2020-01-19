//
// Created by Ilya Sysoi on 1/18/20.
//

#ifndef JSON_READER_H
#define JSON_READER_H

#include <string>
#include "JSON.h"
#include <stack>

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

class Reader {
public:
    Reader() {};

    ~Reader() = default;

    JSON parse(const std::string &jsonString);

private:
    JSON root;
    std::stack<std::string> s;
    std::stack<JSON::Value> s_value;

    // Parser variables
    enum stack_map {
        list_open,
        list_close,
        object_open,
        object_close,
        colon,
        comma,
        buffer,
        follow
    };
    std::map<std::string, stack_map> stack_conversion = {
            {"[",      list_open},
            {"]",      list_close},
            {"{",      object_open},
            {"}",      object_close},
            {":",      colon},
            {",",      comma},
            {"buffer", buffer}
    };

    // FSM
    enum state {
        int_value,
        double_value,
        bool_value,
        string_value,
        null_value,
        default_value,
        bad_state
    };

    state fsm(std::string);

    // Helpers
    bool isDeliminator(char);

    void pushBuffer();


    // Parser helper functions
    void insert(std::string &);

    void addJSONElement();

    void addArrayElement();

    template<typename T>
    void insert(std::string &, T (*)(const std::string &));

    template<typename T>
    void insert();

    // Parser
    void parser(const std::string &cursor);
};


template<typename T>
void Reader::insert(std::string &value, T (*fptr)(const std::string &)) {
    T T_value(fptr(value));
    s_value.push(T_value);
}

template<typename T>
void Reader::insert() {
    T T_value;
    s_value.push(T_value);
}

//class Reader {
//public:
//    JSON parse(std::string json);
//private:
//    JSON parseKeyValue(std::string keyValueString);
//    JSON parseArray(std::string arrayString);
//};

#endif //JSON_READER_H
