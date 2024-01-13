﻿#include <iostream>
#include <vector>
#include "BinomialHeap.h"
#include "BinomialTree.h"

using namespace std;

Heap::Heap() : size(0) {}

Heap::~Heap() {
    if (size > 0) {
        delete[] trees;
        delete[] used;
    }
}

void Heap::print() const {
    setlocale(LC_ALL, "Russian");
    cout << "\nПечать кучи заказа: " << size << endl;
    for (int i = 0; i < size; i++) {
        if (used[i]) {
            cout << "\nкуча: " << i << endl;
            trees[i].print();
        }
        else {
            cout << "\nкуча: " << i << " пусто" << endl;
        }
    }
}

void Heap::grow(const int min_size) {

    int new_size = 0;

    if (min_size < size) {
        new_size = size;
        if (used[size - 1]) new_size++;
    }
    else {
        new_size = min_size + 1;
    }

    if (new_size != size) {
        Tree* treet = new Tree[new_size];
        bool* boolt = new bool[new_size];
        for (int i = 0; i < size; i++)
            if (used[i]) {
                treet[i] = trees[i];
                boolt[i] = true;
            }
            else {
                boolt[i] = false;
            }
        for (int i = size; i < new_size; i++) boolt[i] = false;

        if (size > 0) {
            delete[] trees;
            delete[] used;
        }
        trees = treet;
        used = boolt;
        size = new_size;
    }
}

void Heap::push(const int value) {
    Leaf element(value);
    merge(element);
}

int Heap::pop() {
    setlocale(LC_ALL, "Russian");
    int min = 0;
    while (min < size && !used[min]) min++;
    if (min == size) throw "Ошибка всплывающего окна с пустым стеком";

    for (int i = 0; i < size; i++) if (used[i]) {
        if (trees[i].getValue() < trees[min].getValue()) min = i;
    }

    int value = trees[min].getValue();
    int order = trees[min].getSize();

    vector<Tree> children(order);

    for (int i = 0; i < order; i++)
        children[i] = trees[min].getChilderen()[i];
    used[min] = false;

    for (int i = 0; i < order; i++) merge(children[i]);

    return value;
}

void Heap::merge(const Tree& tree) {
    grow(tree.getSize());

    Tree hold;
    hold = tree;
    int order = hold.getSize();

    while (used[order]) {
        hold = hold + trees[order];
        used[order] = false;
        order++;
    }

    trees[order] = hold;
    used[order] = true;
}

Heap& Heap::operator+=(const Heap& heap) {
    for (int i = 0; i < heap.size; i++) {
        if (heap.used[i]) merge(heap.trees[i]);
    }

    return (*this);
}

