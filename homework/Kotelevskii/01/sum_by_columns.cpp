#include<iostream>
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
int main()
{
	const std::size_t SIZE = 10000;
	int**a = new int*[SIZE];
	for (std::size_t i = 0; i < SIZE; i++)
	{
		a[i] = new int[SIZE];
		for (std::size_t j = 0; j < SIZE; j++)
			a[i][j] = i;
	}

	{
		Timer t;
		volatile int sum = 0;
		for (std::size_t i = 0; i < SIZE; i++)
			for (std::size_t j = 0; j < SIZE; j++)
				sum += a[j][i];
	}
	for (std::size_t i = 0; i < SIZE; i++)
		delete[] a[i];
	delete[]a;
}
