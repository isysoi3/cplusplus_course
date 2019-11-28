//
// Created by Ilya Sysoi on 11/25/19.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <vector>
#include <map>
#include <variant>
#include <string>

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
    JSON(JSON const &json);
    JSON(const std::string&);

//
//    void addValue(const std::string& key, Value value);
//    bool tryToAddValue(const std::string& key, Value value);
//
//    const Value& getValue(const std::string& key);

    bool isEmpty();

//
//    bool operator==(const JSON& json);
};


#endif //JSON_JSON_H
