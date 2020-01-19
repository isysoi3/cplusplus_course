//
// Created by Ilya Sysoi on 11/25/19.
//

#include "JSON.h"
#include "Reader/Reader.h"
#include "JSONException.h"

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
            throw JSONException("Invalid argument");
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
        } else {
            throw JSONException("Invalid argument");
        }
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
        throw JSONException("Failed to add KeyValue to Array");
    }
}

void JSON::addValue(const JSON::Value &value) {
    if (holds_alternative<Array>(root)) {
        auto v_array = get<Array>(root);
        v_array.push_back(value);
        root = v_array;
    } else {
        throw JSONException("Failed to add value to KeyValue");
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

string JSON::dictToString(const KeyValue &map) const {
    string rez = "";
    int i = map.size();
    for (const auto&[key, value] : map) {
        rez += " \"" + key + "\" : " + valueToString(value);
        rez += i != 1 ? ", " : " ";
        --i;
    }
    return rez;
}

string JSON::arrayToString(const Array &array) const {
    string rez = "";
    int i = array.size();
    for (const auto &value : array) {
        rez += valueToString(value);
        rez += i != 1 ? ", " : "";
        --i;
    }
    return rez;
}

string JSON::valueToString(const Value &value) {
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
}

std::ostream &operator<<(std::ostream &out, const JSON::Value &v) {
    out << JSON::valueToString(v);
    return out;
}

bool operator==(const JSON& l, const JSON& r) {
    if (l.root.index() != r.root.index()) return false;
    return visit([r](JSON::Object &&arg) -> bool {
        if (holds_alternative<JSON::KeyValue>(arg)) {
            auto v_map_l = get<JSON::KeyValue>(arg);
            auto v_map_r = get<JSON::KeyValue>(arg);
            return v_map_l == v_map_r;
        } else if (holds_alternative<JSON::Array>(arg)) {
            auto v_array_l = get<JSON::Array>(arg);
            auto v_array_r = get<JSON::Array>(arg);
            return v_array_l == v_array_r;
        }
    }, l.root);
}

bool operator!=(const JSON& l, const JSON& r) {
    return l == r ? false : true;
}

bool operator==(const JSON::Value& l, const JSON::Value& r) {
    if (l.index() != r.index()) return false;
    return visit([r](JSON::Value &&arg) -> bool {
        if (holds_alternative<void *>(arg)) {
            return true;
        } else if (holds_alternative<bool>(arg)) {
            auto v_bool_l = get<bool>(arg);
            auto v_bool_r = get<bool>(r);
            return v_bool_l == v_bool_r;
        } else if (holds_alternative<int>(arg)) {
            auto v_int_l = get<int>(arg);
            auto v_int_r = get<int>(r);
            return v_int_l == v_int_r;
        } else if (holds_alternative<double>(arg)) {
            auto v_double_l = get<double>(arg);
            auto v_double_r = get<double>(r);
            return v_double_l == v_double_r;
        } else if (holds_alternative<string>(arg)) {
            auto v_string_l = get<double>(arg);
            auto v_string_r = get<double>(r);
            return v_string_l == v_string_r;
        } else if (holds_alternative<JSON>(arg)) {
            auto v_json_l = get<JSON>(arg);
            auto v_json_r = get<JSON>(r);
            return v_json_l == v_json_r;
        }
    }, l);
}

bool operator!=(const JSON::Value& l, const JSON::Value& r) {
    return l == r ? false : true;
}

JSON::Value JSON::operator[](int index) const {
    if (std::holds_alternative<Array>(root)) {
        auto v_array = std::get<Array>(root);
        if (index < 0 && index >= v_array.size()) throw JSONException("Invalid index");
        return v_array[index];
    } else {
        throw JSONException("Bad access with string to array");
    }
}

JSON::Value JSON::operator[](const std::string &key) const {
    if (std::holds_alternative<KeyValue>(root)) {
        auto v_map = std::get<KeyValue>(root);
        return v_map[key];
    } else {
        throw JSONException("Bad access with string to array");
    }
};

std::optional<JSON::Array> JSON::asArray() {
    if (std::holds_alternative<Array>(root)) {
        return std::get<Array>(root);
    } else {
        return std::nullopt;
    }
}