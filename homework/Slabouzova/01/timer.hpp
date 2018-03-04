#include <iostream>
#include <chrono>
#include <cmath>

class Timer
{
    int n_iters;
public:
    // n_iters is a number of  iterations for more precision
    Timer(int n_iters)
        : start_(std::chrono::high_resolution_clock::now()),
        n_iters(n_iters)
    {
        std::cout << "timer started" << std::endl;
    }

    ~Timer()
    {   // output in seconds
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(finish - start_).count() / 
                                                    static_cast<double>(n_iters) << " s" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};
