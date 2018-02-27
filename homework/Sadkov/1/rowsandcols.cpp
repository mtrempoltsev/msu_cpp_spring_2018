#include <chrono>
#include <iostream>
#include <vector> 

const int arrSize = 10000;

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

int sum_by_rows(int ** arr)
{
	volatile int res = 0;
	Timer t;
	for(int i = 0; i < arrSize; i++)
		for(int j = 0; j < arrSize; j++)
			res += arr[i][j];
	return res;
}

int sum_by_cols(int ** arr)
{
	volatile int res = 0;
	Timer t;
	for(int j = 0; j < arrSize; ++j)
		for(int i = 0; i < arrSize; ++i)
			res += arr[i][j];
	return res;
}

int v_sum_by_rows(const std::vector< std::vector<int> >& arr)
{
	volatile int res = 0;
	Timer t;
	for(int i = 0; i < arrSize; i++)
		for(int j = 0; j < arrSize; i++)
			res += arr[i][j];
	return res;
}

int v_sum_by_cols(const std::vector< std::vector<int> >& arr)
{
	volatile int res = 0;
	Timer t;
	for(int j = 0; j < arrSize; j++)
		for(int i = 0; i < arrSize; i++)
			res += arr[i][j];
	return res;
}


int main()
{
	int ** arr = new int *[arrSize];
	for(int i = 0; i < arrSize; ++i)
		arr[i] = new int [arrSize];
	std::cout << sum_by_rows(arr) << std::endl;
	std::cout << sum_by_cols(arr) << std::endl;
	for(int i = 0; i < arrSize; ++i)
		delete[] arr[i];
	delete[] arr;
	std::vector< std::vector<int> > arr1 = std::vector< std::vector<int> >(arrSize, std::vector<int>(arrSize));	
	std::cout << v_sum_by_rows(arr1) << std::endl;
	std::cout << v_sum_by_cols(arr1) << std::endl;
	return 0;
}
