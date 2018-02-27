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

int by_rows(int ** arr, int size)
{
	int s = 0, i, j;
	Timer t;
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			s += arr[i][j];
	return s;
}

int by_cols(int ** arr, int size)
{
	int s = 0, i, j;
	Timer t;
	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			s += arr[j][i];
	return s;
}

int main()
{
	const int sz = 5000;
	int ** arr = new int *[sz];
	for(int i = 0; i < sz; ++i)
		arr[i] = new int [sz];
	std::cout << by_rows(arr, sz) << std::endl;
	std::cout << by_cols(arr, sz) << std::endl;
	for(int i = 0; i < sz; ++i)
		delete[] arr[i];
	delete[] arr;
	return 0;
}
