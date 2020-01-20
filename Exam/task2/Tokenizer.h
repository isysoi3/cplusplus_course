//
// Created by Ilya Sysoi on 1/20/20.
//

#ifndef TASK2_TOKENIZER_H
#define TASK2_TOKENIZER_H

#include <string>
#include <utility>
#include <vector>

class Tokenizer {
private:
    std::vector<std::string_view> splited;

    static std::vector<std::string_view> parse(const std::string& str, const std::string& splitter) {
        int pos = 0;
        std::vector<std::string_view> rez;
        while(auto it = str.find(splitter, pos)) {
            if (it == std::string::npos) {
                rez.push_back(str.substr(pos, str.size() - pos));
                break;
            };
            auto tmp = str.substr(pos, it - pos);
            rez.push_back(str.substr(pos, it - pos));
            pos = it + 1;
        }
        return rez;
    }

public:

    typedef std::vector<std::string_view>::iterator iterator;

    Tokenizer(const std::string& str, const std::string& splitter) {
        splited = Tokenizer::parse(str, splitter);
    }

    iterator begin() {
        return splited.begin();
    }

    iterator end() {
        return splited.end();
    }

};


#endif //TASK2_TOKENIZER_H
