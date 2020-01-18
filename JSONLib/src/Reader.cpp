//
// Created by Ilya Sysoi on 1/18/20.
//

#include "Reader.h"
#include "Helpers.cpp"

//{ "1" : null,  "array" : [{ "1" : null }, { "1" : null }],  "json" : { "1" : 1 } }

using namespace std;

//ReaderException invalidString() {
//    return ReaderException("invalid string format");
//}
//JSON Reader::parseKeyValue(string keyValueString) {
//    JSON json;
//    if (keyValueString.empty()) return json;
//    int i = 0;
//    int first;
//    int last;
//    while (i < keyValueString.size()) {
//        if (keyValueString[i] == ' ') {
//            i++;
//            continue;
//        }
//        if (keyValueString[i] == '{') {
//            i++;
//            continue;
//        }
//        if (keyValueString[i] == '[') {
//            i++;
//            continue;
//        }
//        if (keyValueString[i] == '"') {
//            string key = parseString()
//        }
//    }
//    for(char c : keyValueString) {
//        if (c == ' ') continue;
//        if (c == '"') {
//            string key = parseString()
//        }
//    }
//    return json;
//}
//
//JSON Reader::parseArray(string arrayString) {
//    return JSON();
//}
//
//JSON Reader::parse(string jsonString) {
//    if (jsonString.empty()) throw ReaderException("invalid string format");
//    int size = jsonString.size();
//    int first = jsonString[0];
//    int last = jsonString[size - 1];
//    bool isArray = first == '[' && last == ']';
//    bool isKeyValue = first == '{' && last == '}';
//    if ((isArray && isKeyValue)
//        || (!isArray && !isKeyValue)) {
//        throw ReaderException("invalid format");
//    }
//    string substr = jsonString.substr(1, size - 2);
//    return isArray ? parseArray(substr) : parseKeyValue(substr);
//}


// helpers
bool Reader::isDeliminator(char value) {
    switch (value) {
        case '[':
            return true;
        case ']':
            return true;
        case '{':
            return true;
        case '}':
            return true;
        case ':':
            return true;
        case ',':
            return true;
        default:
            return false;
    }
}

void Reader::pushBuffer() {
    s.pop();
    s.push("buffer");
}

// Parsing
JSON Reader::parse(const string& jsonString) {
    std::string capture = "";
    std::vector<std::string> scan;

    for(char c : jsonString) {
        if (isDeliminator(c)) {
            trim(capture);
            if (!capture.empty()) {
                scan.emplace_back(capture);
                capture = "";
            }
            scan.emplace_back(string(&c, 1));
        } else {
            capture += c;
        }
    }
    scan.emplace_back("terminate");
    for (auto & it : scan) { parser(it); }
    JSON json = get<JSON>(s_value.top());
    s_value.pop();
    return json;
}

void Reader::parser(const std::string & cursor) {
    if (!s.empty()) {
        std::string value = s.top();
        stack_map stack_value = stack_conversion.find(value) != stack_conversion.end()
                ? stack_conversion[value]
                : follow;

        switch (stack_value) {
            case buffer:
                s.pop();
                break;
            case list_open:
                insert<JSON::Array>();
                if (cursor == "]") {
                    pushBuffer();
                    return;
                }
                break;
            case list_close:
                addArrayElement();
                s.pop();
                s.pop();
                break;
            case object_open:
                insert<JSON>();
                if (cursor == "}") {
                    pushBuffer();
                    return;
                }
                break;
            case object_close:
                addJSONElement();
                s.pop();
                s.pop();
                break;
            case colon:
                s.pop();
                break;
            case comma:
                s.pop();
                if (s.top() == "{") {
                    addJSONElement();
                } else {
                    addArrayElement();
                }
                break;
            default:
                s.pop();
                switch (fsm(value)) {
                    case string_value:
                        insert(value);
                        break;
                    case int_value:
                        insert<int>(value, toInt);
                        break;
                    case double_value:
                        insert<double>(value, toDouble);
                        break;
                    case bool_value:
                        insert<bool>(value, toBool);
                        break;
                    case null_value:
                        insert<void*>();
                        break;
                    default:
                        throw ReaderException("Bad state");
                }
//            case follow:
//                break;
        }
        s.push(cursor);
    } else {
        s.push(cursor);
    }
}

// FSM
Reader::state Reader::fsm(std::string value) {
    state current = default_value;
    for(char point : value) {
        if (point == '"' & current == default_value) {
            current = string_value;
            break;
        } else if (isdigit(point)) {
            if (current == default_value | current == int_value) {
                current = int_value;
                continue;
            } else if (current == double_value) {
                continue;
            } else {
                current = bad_state;
                break;
            }
        } else if (point == '.' & current == int_value) {
            current = double_value;
            continue;
        } else if (point == 'f' & current == double_value) {
            continue;
        } else if (current == default_value) {
            if (value == "true" | value == "false") {
                current = bool_value;
                break;
            } else if (value == "null") {
                current = null_value;
                break;
            } else {
                current = bad_state;
                break;
            }
        } else {
            current = bad_state;
            break;
        }
    }
    return current;
}

// Parser Helper functions
void Reader::insert(std::string & value) {
    value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
    s_value.push(value);
}

void Reader::addJSONElement() {
    JSON::Value value_read;
    std::string key_read;

    value_read = s_value.top();
    s_value.pop();
    key_read = std::get<std::string>(s_value.top());
    s_value.pop();

    std::get<JSON>(s_value.top()).addValue(key_read, value_read);
}

void Reader::addArrayElement() {
    JSON::Value value_read;

    value_read = s_value.top();
    s_value.pop();

    std::get<JSON>(s_value.top()).addValue(value_read);
}