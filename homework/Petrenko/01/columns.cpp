#include <chrono>
#include <iostream>

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

using namespace std;
using myarr = int(*)[10000][10000];

int main() {
    int * data = new int[10000 * 10000];
    myarr arr = (myarr) data;
    for (int i = 0; i < 10000; i++) {
        for(int j = 0; j < 10000; j++) {
            (*arr)[i][j] = i + j;
        }
    }
    //sum by columns
    for(int k = 0; k < 10; k++){
        Timer time_c;
        int sum_c = 0;
        for(int j = 0; j < 10000; j++) {
            for (int i = 0; i < 10000; i++) {
                sum_c += (*arr)[i][j];
            }
        }
        cerr << sum_c << endl;
        cout << "Sum by columns time on try #" << k + 1<< " is ";
    }
    delete[] data;
    return 0;
}
