#pragma once

#include "BinomialTree.h"

class Heap {
private:
    int size;
    Tree* trees;
    bool* used;

    void merge(const Tree& tree);

    void grow(const int min_size);

public:
    Heap();
    ~Heap();

    void print() const;

    void push(const int value);

    int pop();

    Heap& operator+=(const Heap& heap);
};
