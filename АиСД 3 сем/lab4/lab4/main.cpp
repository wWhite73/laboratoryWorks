#include <iostream>
#include "BinomialHeap.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Heap heap;

    heap.push(1);
    heap.push(4);
    heap.push(2);
    heap.push(8);
    heap.push(9);
    heap.push(6);
    heap.push(10);
    heap.push(11);
    heap.push(19);
    heap.push(13);
    heap.push(17);
    heap.push(15);
    heap.push(16);
    heap.push(14);
    heap.push(18);
    heap.push(12);

    heap.print();

    int min = heap.pop();

    heap.print();

    return 0;
}
