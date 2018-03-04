#include <chrono>
#include <iostream>
#define SIZE 1000

class Timer
{
public:
    Timer()
        : start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};

int sum_by_mode(int size, int** data){
    Timer t;
    int sum = 0;    
    for (int j = 0; j < size; j++)
        for (int i = 0; i < size; i++)
            sum += data[j][i];
    return sum;
}


int main(void) {
    int** data = new int*[SIZE];
    for (int i = 0; i < SIZE; i++)
        data[i] = new int[SIZE];
    printf("->>%d\n", sum_by_mode(SIZE, data));

    for(int i = 0; i < SIZE; i++) {
        delete[] data[i];
    }
    delete[] data;
    return 0;
}



