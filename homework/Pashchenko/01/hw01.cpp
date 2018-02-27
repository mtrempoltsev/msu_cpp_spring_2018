#include <chrono>
#include <iostream>
#include <stdlib.h>
using namespace std;

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

void rows(int **ptrarray, int N)
{
    int sum1 = 0;
    Timer obj1;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            sum1 += ptrarray[i][j];
    }
    cout << "rows method: " << sum1 << "\ntime: " << endl;
}

void cols(int **ptrarray, int N)
{
    int sum2 = 0;
    Timer obj2;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            sum2 += ptrarray[j][i];
    }
    cout << "columns method: " << sum2 << "\ntime: "<< endl;

}

int main(void)
{
    const int N = 10000;

    int **ptrarray = new int* [N]; //строки
    for (int count = 0; count < N; count++)
        ptrarray[count] = new int [N]; //столбцы

    for(int row = 0; row < N; row++)
    {
        for(int col = 0; col < N; col++)
            ptrarray[row][col] = (rand() % 10 + 1) / int((rand() % 10 + 1));
    }

    rows(ptrarray, N);
    cols(ptrarray, N);

    for (int i = 0; i < N; i++)
        delete []ptrarray[i];

    delete []ptrarray;

    return 0;
}
