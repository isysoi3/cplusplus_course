//
// Created by Ilya Sysoi on 1/18/20.
//

#include <string>

static int toInt(const std::string &value) {
    return stoi(value);
}

static double toDouble(const std::string &value) {
    return stod(value);
}

static bool toBool(const std::string &value) {
    return value == "true";
}

template<typename ... T>
static bool multiComparision(const char scope, T ... args) {
    return (scope == (args || ...));
}

static bool isDigit(const char c) {
    return multiComparision<char>(c, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0');
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}