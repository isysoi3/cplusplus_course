//
// Created by Ilya Sysoi on 11/25/19.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <vector>
#include <map>
#include <variant>
#include <string>
#include <utility>
#include <iostream>

class JSON {
public:
    using Value = std::variant<void *,
            bool,
            int,
            double,
            std::string,
            JSON>;
    using KeyValue = std::map<std::string, Value>;
    using Array = std::vector<Value>;
    using Object = std::variant<KeyValue, Array>;

    JSON();

    JSON(Array array);

    JSON(const JSON &json);

    void addValue(const std::string &key, Value value);

    void addValue(const JSON::Value &value);

    template<typename T>
    T *getValue(const std::string &key);

    bool isEmpty();

    bool isArray();

    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &out, const JSON &j);

    friend std::ostream &operator<<(std::ostream &out, const Value &v);

    friend std::istream &operator>>(std::istream &in, JSON &j);

    friend bool operator==(const JSON& l, const JSON& r);

    friend bool operator!=(const JSON& l, const JSON& r);

    friend bool operator==(const Value& l, const Value& r);

    friend bool operator!=(const Value& l, const Value& r);

    Value operator[](const std::string &key) const;

    Value operator[](int index) const;

private:
    Object root;

    std::string dictToString(const KeyValue &map) const;

    std::string arrayToString(const Array &array) const;

    static std::string valueToString(const Value &value);

};

template<typename T>
T *JSON::getValue(const std::string &key) {
    if (std::holds_alternative<KeyValue>(root)) {
        KeyValue v_map = std::get<KeyValue>(root);
        return std::get_if<T>(&v_map[key]);
    } else {
        return nullptr;
    }
}

#endif //JSON_JSON_H
