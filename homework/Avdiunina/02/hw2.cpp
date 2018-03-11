//
// Created by polina997 on 3/3/18.
//
#include <iostream>
#include "numbers.dat"
#include <chrono>
using namespace std;

class Timer
{
public:
    Timer()
            : start_(chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        const auto finish = chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<chrono::microseconds>(finish - start_).count() << " us" << endl;
    }

private:
    const chrono::high_resolution_clock::time_point start_;
};

int bin_search(const int *array, int l, int r, int key)
{
    int middle = (l + r) / 2;
    if (l > r)
        return -1;


    if (key < array[middle])
        return bin_search(array, l, middle - 1, key);
    else if (key > array[middle])
        return bin_search(array, middle + 1, r, key);
    else
        return middle;
}


void ert(bool *array, int size) {
    for (int i = 0; i < size; i++)
        array[i] = true;

    for (int i = 2; ((i*i) < size); i++) {
        if (array[i])
            for (int j = (i*i); j < size; j += i) {
               array[j] = false;
            }
    }
}


int main(int argc, char* argv[])
{
    if (argc < 3 || argc % 2 == 0)
        return -1;

    bool *array;
    array = new bool[Data[Size - 1]];

    Timer total_time;
    ert(array, Size - 1);

    Timer test_time;
    int l, r;
    for (int i = 1; i < argc; i += 2) {
        int arg1 = atoi(argv[i]);
        int arg2 = atoi(argv[i + 1]);
        l = bin_search(Data, 0, Size, arg1);
        r = bin_search(Data, l, Size, arg2);

        int count = 0;
        if (l == -1)
            cout << 0 << endl;
        else {
            for (int j = l; j <= r; j++) {
                if (array[Data[j]]) {
                    count++;
                }
            }
        }

        cout << count << endl;
    }
    delete [] array;
    return 0;
}


