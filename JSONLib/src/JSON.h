//
// Created by Ilya Sysoi on 11/25/19.
//

#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <string>
#include <map>

class JSON {
private:
    std::map<std::string, std::string> tmp;
public:
    JSON();
    JSON(const std::string&);
    bool isEmpty();
};


#endif //JSON_JSON_H
