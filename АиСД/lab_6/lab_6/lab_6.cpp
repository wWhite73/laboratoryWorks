#include <iostream>
using namespace std;

class SortAlgo {
    int ;
};

int main() {
    void SortAlgo::selectionSort(int data[], int lenD)
         {
        int j = 0;
        int tmp = 0;
        for (int i = 0; i < lenD; i++) {
            j = i;
            for (int k = i; k < lenD; k++) {
                if (data[j] > data[k]) {
                    j = k;
                }
            }
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }
    }

    void SortAlgo::bubbleSort(int data[], int lenD)
    {
        int tmp = 0;
        for (int i = 0; i < lenD; i++) {
            for (int j = (lenD - 1); j >= (i + 1); j--) {
                if (data[j] < data[j - 1]) {
                    tmp = data[j];
                    data[j] = data[j - 1];
                    data[j - 1] = tmp;
                }
            }
        }
    }
    void SortAlgo::insertionSort(int data[], int lenD)
    {
        int key = 0;
        int i = 0;
        for (int j = 1; j < lenD; j++) {
            key = data[j];
            i = j - 1;
            while (i >= 0 && data[i] > key) {
                data[i + 1] = data[i];
                i = i - 1;
                data[i + 1] = key;
            }
        }
    }

}