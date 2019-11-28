//
// Created by Ilya Sysoi on 11/25/19.
//

#include "JSON.h"


// constructors
JSON::JSON() = default;

//JSON::JSON(JSON::Array array) {
//    object = array;
//}
//
//JSON::JSON(JSON const &json) {
//    object = json.object;
//}
//
//JSON::JSON(const std::string &) {
//
//}

//methods

bool JSON::isEmpty() {
    return std::visit([](Object &&arg) -> bool {
        if (std::holds_alternative<KeyValue>(arg)) {
            auto v_map = std::get<KeyValue>(arg);
            return v_map.empty();
        } else if (std::holds_alternative<Array>(arg)) {
            auto v_array = std::get<Array>(arg);
            return v_array.empty();
        }
        return false;
    }, root);
}
//void JSON::addValue(const std::string &key, JSON::Value value) {
//    map[key] = std::move(value);
//}
//
//bool JSON::tryToAddValue(const std::string &key, JSON::Value value) {
//    if (map.find(key) == map.end()) {
//        addValue(key, value);
//        return true;
//    } else {
//        return false;
//    }
//}
//
//const JSON::Value& JSON::getValue(const std::string &key) {
//    if (map.find(key) == map.end()) {
//        return nullptr;
//    } else {
//        return map[key];
//    }
//}
//
//bool JSON::operator==(const JSON& json) {
//    return this->map == json.map;
//}
//
//JSON::JSON(JSON json) {
//
//}

