#pragma once

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
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count();
	}
	
private:
	const std::chrono::high_resolution_clock::time_point start_;
};

int recursive_fibonacci (int num) {
	if (num == 0 || num == 1)
		return 1;
	volatile int a = recursive_fibonacci(num - 1) + recursive_fibonacci(num - 2);
	return a;
}
