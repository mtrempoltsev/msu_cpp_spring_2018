#include <chrono>
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 

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
	int N = 10000; 
	int **A = (int **)malloc(N*sizeof(int *)); 
	for (int i = 0; i < N; i++) { 
		A[i] = (int *)malloc(N*sizeof(int)); 
	} 

        for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i][j] = i + j;
		}
	}

	{ 
   	int tmp = 0; 
	Timer t; 
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			tmp += A[i][j]; 
	
        std::cout << "res = " << tmp << "\n"; }

        { 
	int tmp = 0; 
	Timer t; 
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			tmp += A[j][i]; 
	
        std::cout << "res = " << tmp << "\n";}
	return 0; 
}

