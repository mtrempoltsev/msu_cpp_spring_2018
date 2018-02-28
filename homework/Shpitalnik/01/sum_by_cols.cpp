#include <iostream>
#include <chrono>

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

static int n = 1000;
static int m = 1000;

int main() {
    int arr[n][m];
    int sum[m];
    for (int k =0; k<m; k++)
        sum[k] =0;
    Timer t;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            sum[j] += arr[i][j];


    return 0;
}
