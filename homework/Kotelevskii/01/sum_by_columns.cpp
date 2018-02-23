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
	const int size_t = 10000;
	int**a = new int*[size_t];
	for (int i = 0; i < size_t; i++)
	{
		a[i] = new int[size_t];
		for (int j = 0; j < size_t; j++)
			a[i][j] = i;
	}

	{
		Timer t;
		volatile int sum = 0;
		for (int i = 0; i < size_t; i++)
			for (int j = 0; j < size_t; j++)
				sum += a[j][i];
	}
	for (int i = 0; i < size_t; i++)
		delete[] a[i];
	delete[]a;
}
