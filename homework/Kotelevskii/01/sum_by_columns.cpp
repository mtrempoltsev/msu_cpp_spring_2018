#include<iostream>
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
int main()
{
	int**a = new int*[10000];
	for (int i = 0; i < 10000; i++)
	{
		a[i] = new int[10000];
		for (int j = 0; j < 10000; j++)
			a[i][j] = i;
	}
	int num_attempts = 10;


	Timer* b=new Timer;
	for (int k = 0; k < num_attempts;k++)
	{
		volatile int sum = 0;
		for (int i = 0; i < 10000; i++)
			for (int j = 0; j < 10000; j++)
				 sum += a[j][i];
	}
	delete b;
	
	for (int i = 0; i < 10000; i++)
		delete[] a[i];
	delete[]a;
}