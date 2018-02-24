#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer(int tn = 1)
        : start_(std::chrono::high_resolution_clock::now()), try_num(tn)
    {
    }

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        const auto delta_time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
        std::cout << "Try #" << try_num << " took " << delta_time << " us" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
    const int try_num;
};

const int mat_size = 10000;
const int iter_count = 10;

using namespace std;
using myarr = int(*)[mat_size][mat_size];

int main() {
	cout << "Testing sum by columns" << endl;
    int * data = new int[mat_size * mat_size];
    myarr arr = (myarr) data;
    for (int i = 0; i < mat_size; i++) {
        for(int j = 0; j < mat_size; j++) {
            (*arr)[i][j] = 1;
        }
    }
    //sum by columns
    for(int k = 1; k <= iter_count; k++){
        Timer time_c(k);
        int sum_c = 0;
        for(int j = 0; j < mat_size; j++) {
            for (int i = 0; i < mat_size; i++) {
                sum_c += (*arr)[i][j];
            }
        }
        cerr << sum_c << endl;
    }
    delete[] data;
    return 0;
}
