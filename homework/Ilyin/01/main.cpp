#include <chrono>
#include <iostream>
#include <cstdlib>

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

void sum_b_cols(int** test, size_t N){
    Timer t;
    int res = 0;

    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < N; j++){
        res += test[j][i];
        }
    }
}

void sum_b_rows(int** test, size_t N){
    Timer t;
    int res = 0;

    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < N; j++){
        res += test[i][j];
        }
    }

}

int main(){

    size_t N = 500;
    int** test = new int*[N];

    for (size_t i = 0; i < N; i++){
        test[i] = new int[N];
    }

    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < N; j++){
        test[i][j] = rand() % N;
        }
    }

    sum_b_cols(test, N);
    sum_b_rows(test, N);
    sum_b_rows_s(test_s, n);

    for (size_t i = 0; i < N; i++){
        delete []test[i];
    }
    
    delete [] test;
    
    return 0;

}
