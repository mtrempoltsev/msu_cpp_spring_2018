#include <chrono>
#include <iostream>

class Timer
{
private:
	const std::chrono::high_resolution_clock::time_point start_;

public:
	Timer() : start_(std::chrono::high_resolution_clock::now())
	{
	}

	~Timer()
	{
		const auto finish = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
	}
};

int fast(int** A, int size)
{
	int sum = 0;
	Timer t;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += A[i][j];
		}
	}
	return sum;
}

int slow(int** A, int size)
{
	int sum = 0;
	Timer t;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += A[j][i];
		}
	}
	return sum;
}

int main(void)
{
	const int size = 10000;
	int** A = new int*[size];
	for (int i = 0; i < size; i++)
		A[i] = new int[size];
	std::cout << "sum = " << fast(A, size) << std::endl; // output sum for ban optimisation
	std::cout << "sum = " << slow(A, size) << std::endl;
	for (int i = 0; i < size; i++)
		delete[] A[i];
	delete[] A;
	return 0;
}