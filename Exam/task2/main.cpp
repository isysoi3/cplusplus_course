#include <iostream>
#include "Tokenizer.h"

int main() {
//    std::cout << "Hello, World!" << std::endl;

    Tokenizer tokenizer = Tokenizer("1231, 2131, 21312, 123", ",");

    for(auto lex : tokenizer) {
        std::cout << lex << std::endl;
    }

    return 0;
}
