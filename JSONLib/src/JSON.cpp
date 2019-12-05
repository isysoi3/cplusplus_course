//
// Created by Ilya Sysoi on 11/25/19.
//

#include "JSON.h"


// constructors
JSON::JSON() = default;

JSON::JSON(JSON::Array array) {
    root = array;
}

//JSON::JSON(JSON const &json) {
//    std::visit([this](Object &&arg) {
//        if (std::holds_alternative<KeyValue>(arg)) {
//            auto v_map = std::get<KeyValue>(arg);
//            root = v_map;
//        } else if (std::holds_alternative<Array>(arg)) {
//            auto v_array = std::get<Array>(arg);
//            root = v_array;
//        }
//    }, json);
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

void JSON::addValue(const std::string &key, JSON::Value value) {
    if (std::holds_alternative<KeyValue>(root)) {
        auto v_map = std::get<KeyValue>(root);
        v_map[key] = std::move(value);
        root = v_map;
    } else {
        return;
    }
}

void JSON::addValue(const JSON::Value& value) {
    if (std::holds_alternative<Array>(root)) {
        auto v_array = std::get<Array>(root);
        v_array.push_back(value);
    } else {
        return;
    }
}

//bool JSON::operator==(const JSON &right) {
//    return this->root.index() != right.root.index();
//}


//bool operator==(const JSON &right) {
//
////    return std::visit([&](auto const& l) {
////
////                      }, root);
//}

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

//
//bool JSON::operator==(const JSON& json) {
//    return this->root == json.root;
//}

//JSON::JSON(JSON json) {
//
//}

