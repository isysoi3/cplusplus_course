//
// Created by Ilya Sysoi on 11/25/19.
//

#include "JSON.h"


// constructors
JSON::JSON() {
    root = KeyValue();
};

JSON::JSON(JSON::Array array) {
    root = array;
}

JSON::JSON(const JSON &json) {
    std::visit([this](Object &&arg) {
        if (std::holds_alternative<KeyValue>(arg)) {
            auto v_map = std::get<KeyValue>(arg);
            this->root = v_map;
        } else if (std::holds_alternative<Array>(arg)) {
            auto v_array = std::get<Array>(arg);
            this->root = v_array;
        } else {
            throw std::invalid_argument("test");
        }
    }, json.root);
}

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

bool JSON::isArray() {
    return root.index() == 1;
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

std::string JSON::toString() {
    return std::visit([this](Object &&arg) -> std::string {
        if (std::holds_alternative<KeyValue>(arg)) {
            auto v_map = std::get<KeyValue>(arg);
            return "{" + this->dictToString(v_map) + "\n}";
        } else if (std::holds_alternative<Array>(arg)) {
            return "1223";
        }
        return "1223";
    }, root);
}

std::string JSON::dictToString(KeyValue map) {
    std::string rez = "";
    for (const auto& [key, value] : map) {
        rez += "\n\t" + key + " : " /*+ value*/;
    }
    return rez;
}