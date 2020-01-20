//
// Created by Ilya Sysoi on 1/20/20.
//

#ifndef TASK1_SEQUANCE_H
#define TASK1_SEQUANCE_H

#include <memory>

template<typename T>
class sequence_iterator;

template<typename T, typename U = T(T)>
class Sequence {
public:
    U *generator;
    T first;

    T get(T current) {
        return (*generator)(current);
    }

    Sequence(T first, U generator) : first(first) {
        this->generator = generator;
    }
};

template<typename T>
class SequenceIterator : public std::iterator<std::input_iterator_tag, T>{
    std::shared_ptr<Sequence<T>> seq;
    T cache;
    int count = 0;
    int total;

public:
    SequenceIterator(std::shared_ptr<Sequence<T>> const &s, int total, int count = 0)
            : seq(s), total(total), count(count) {
        cache = seq->first;
    }

    SequenceIterator& operator++() {
        cache = seq->get(cache);
        ++count;
        return *this;
    }

    SequenceIterator operator++(int) {
        cache = seq->get(cache);
        ++count;
        return *this;
    }

    SequenceIterator end() {
        return SequenceIterator(seq, total, total);
    }

    SequenceIterator begin() {
        return SequenceIterator(seq, total, 0);
    }

    T& operator*() {
        return cache;
    }

    bool operator==(const SequenceIterator &b) const {
        return count == b.count;
    }

    bool operator!=(const SequenceIterator &b) const {
        return !(*this == b);
    }
};

#endif //TASK1_SEQUENCE_H

