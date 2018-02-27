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
        res += test[i][j];
        }
    }
}

void sum_b_rows(int** test, size_t N){
    Timer t;
    int res = 0;

    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < N; j++){
        res += test[j][i];
        }
    }

}


void sum_b_cols_s(int test[][500], const size_t N){
    Timer t;
    int res = 0;

    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < N; j++){
        res += test[i][j];
        }
    }
}

void sum_b_rows_s(int test[][500], const size_t N){
    Timer t;
    int res = 0;

    for (size_t i = 0; i < N; i++){
        for (size_t j = 0; j < N; j++){
        res += test[j][i];
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

    const size_t n = 500;

    int test_s[n][n];

    for (size_t i = 0; i < n; i++){
        for (size_t j = 0; j < n; j++){
        test_s[i][j] = rand() % n;
        }
    }

    sum_b_cols_s(test_s, n);
    sum_b_rows_s(test_s, n);

    for (size_t i = 0; i < N; i++){
        delete []test[i];
    }
    
    delete [] test;
    
    return 0;

}
