#include <iostream>
#include <chrono>
#include <ctime>
#include <climits>


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

int main()
{
    constexpr int N = 10000, M = 10000;
    int **a = new int*[N];
    long long sum = 0;
    srand(time(nullptr));
    for (int i = 0; i < N; ++i) {
        a[i] = new int[M];
        for (int j = 0; j < M; ++j) {
            a[i][j] = rand() - (__INT_MAX__ >> 1);
//            std::cout << a[i][j] << ' ';
        }
//        std::cout << std::endl;
    } //init
    
    std::cout << std::endl;
    
    {
        Timer t;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                sum += a[i][j];
            }
        }
    }
    std::cout << sum << std::endl;
    for (int i = 0; i < N; ++i) {
        delete[] a[i];
    }
    delete[] a;
    return 0;
}
