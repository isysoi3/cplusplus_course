#include <iostream>
#include <vector>
#include "Sequence.h"

int increment(int i) {
    return i + 1;
}

int main() {
    auto seq = std::make_shared<Sequence<int>>(0, &increment);
    SequenceIterator<int> it(seq, 10);
    std::vector<int> v(it.begin(), it.end());

    for(auto value : v) {
        std:: cout << value << " ";
    }

    return 0;
}
