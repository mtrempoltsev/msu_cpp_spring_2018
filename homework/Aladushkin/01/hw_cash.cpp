#include <stdio.h> 
#include <stdlib.h>  

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
	int N = 10000;

	int **A = (int **)malloc(N*sizeof(int *));
	for (int i = 0; i < N; i++)
		A[i] = (int *)malloc(N*sizeof(int));

	{
		volatile int tmp = 0;
		Timer t;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				tmp += A[i][j];
	}
	
	{
		volatile int tmp = 0;
		Timer t;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				tmp += A[j][i]; 
	}

	for (int i = 0; i < N; i++)
		free(A[i]);

	free(A);

	return 0;
}