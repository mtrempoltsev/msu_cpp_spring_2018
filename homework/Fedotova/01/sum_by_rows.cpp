#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#define SIZE_r 10000
#define SIZE_c 10000

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


int main() {
	srand(time(NULL));

	int ** a = new int * [SIZE_r];
	for (int i = 0; i < SIZE_r; i++) {
		a[i] = new int [SIZE_c];
		for (int j = 0; j < SIZE_c; j++)
			a[i][j] = rand();
	}

	int sum = 0;
	{
		Timer t;
		for (int i = 0; i < SIZE_r; i++)
			for (int j = 0; j < SIZE_c; j++)
				sum += a[i][j];
	}
	cout << sum << endl;

	for (int i = 0; i < SIZE_r; i++)
		delete[] a[i];
	delete[] a;

	return 0;
}
