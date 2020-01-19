//
// Created by Ilya Sysoi on 11/25/19.
//

#include "JSON.h"
#include "Reader.h"

using namespace std;

// constructors
JSON::JSON() {
    root = KeyValue();
};

JSON::JSON(JSON::Array array) {
    root = array;
}

JSON::JSON(const JSON &json) {
    visit([this](Object &&arg) {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            this->root = v_map;
        } else if (holds_alternative<Array>(arg)) {
            auto v_array = get<Array>(arg);
            this->root = v_array;
        } else {
            throw invalid_argument("test");
        }
    }, json.root);
}

//methods
bool JSON::isEmpty() {
    return visit([](Object &&arg) -> bool {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            return v_map.empty();
        } else if (holds_alternative<Array>(arg)) {
            auto v_array = get<Array>(arg);
            return v_array.empty();
        }
        return false;
    }, root);
}

bool JSON::isArray() {
    return root.index() == 1;
}

void JSON::addValue(const string &key, JSON::Value value) {
    if (holds_alternative<KeyValue>(root)) {
        auto v_map = get<KeyValue>(root);
        v_map[key] = value;
        root = v_map;
    } else {
        return;
    }
}

void JSON::addValue(const JSON::Value &value) {
    if (holds_alternative<Array>(root)) {
        auto v_array = get<Array>(root);
        v_array.push_back(value);
        root = v_array;
    } else {
        return;
    }
}

string JSON::toString() const {
    return visit([this](Object &&arg) -> string {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            return "{" + this->dictToString(v_map) + "}";
        } else if (holds_alternative<Array>(arg)) {
            auto v_array = get<Array>(arg);
            return "[" + this->arrayToString(v_array) + "]";
        }
    }, root);
}

string JSON::dictToString(KeyValue map) const {
    string rez = "";
    int i = map.size();
    for (const auto&[key, value] : map) {
        rez += " \"" + key + "\" : " + valueToString(value);
        rez += i != 1 ? ", " : " ";
        --i;
    }
    return rez;
}

string JSON::arrayToString(Array array) const {
    string rez = "";
    int i = array.size();
    for (const auto &value : array) {
        rez += valueToString(value);
        rez += i != 1 ? ", " : "";
        --i;
    }
    return rez;
}

string JSON::valueToString(Value value) const {
    return visit([](Value &&arg) -> string {
        if (holds_alternative<void *>(arg)) {
            return "null";
        } else if (holds_alternative<bool>(arg)) {
            auto v_bool = get<bool>(arg);
            return v_bool ? "true" : "false";
        } else if (holds_alternative<int>(arg)) {
            auto v_int = get<int>(arg);
            return to_string(v_int);
        } else if (holds_alternative<double>(arg)) {
            auto v_double = get<double>(arg);
            string str = to_string(v_double);
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            return str;
        } else if (holds_alternative<string>(arg)) {
            auto v_string = get<string>(arg);
            return "\"" + v_string + "\"";
        } else if (holds_alternative<JSON>(arg)) {
            auto v_json = get<JSON>(arg);
            return v_json.toString();
        }
    }, value);
}

std::ostream &operator<<(std::ostream &out, const JSON &j) {
    out << j.toString();
    return out;
}

std::istream &operator>>(std::istream &in, JSON &j) {
    std::string str;
    std::getline(in, str);
    j = Reader().parse(str);
    return in;
};