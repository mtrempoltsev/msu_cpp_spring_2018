#include <chrono>
#include <iostream>
#include <chrono>
#include<ctime>

using namespace std;

int main() {
    srand(time(0));
    int sum = 0;
    const unsigned int size = 10000;
    int **array;
    array = new int * [size];
    for(int i = 0; i < size; ++i){
        array[i] = new int[size];
    }
    
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            array[i][j] = rand() % 100;
        }
    }
    unsigned int start = clock();
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            sum += array[i][j];
        }
    }
    unsigned int end = clock();
    cout << (end - start) / 1000.0 << endl;
    return 0;
}


