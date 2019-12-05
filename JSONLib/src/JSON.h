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

class JSON {
private:
    using Value = std::variant<void*,
                               bool,
                               int,
                               double,
                               std::string,
                               JSON>;
    using KeyValue = std::map<std::string, Value>;
    using Array = std::vector<Value>;
    using Object = std::variant<KeyValue, Array>;

    Object root;

public:
    JSON();
    JSON(Array array);

    void addValue(const std::string& key, Value value);
    void addValue(const JSON::Value& value);


    template<typename T>
    T* getValue(const std::string &key);

    bool isEmpty();

    bool operator==(const JSON& right);
};

template<typename T>
T* JSON::getValue(const std::string &key){
    if (std::holds_alternative<KeyValue>(root)) {
        KeyValue v_map = std::get<KeyValue>(root);
        return std::get_if<T>(&v_map[key]);
    } else {
        return nullptr;
    }
};



#endif //JSON_JSON_H
