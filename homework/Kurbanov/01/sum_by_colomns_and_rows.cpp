#include <iostream>
#include <chrono>

using namespace std;

const int N = 10000;

class Timer
{
public:
	Timer()
		: start_(std::chrono::high_resolution_clock::now()) {}

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
	int **array = new int*[N];
	for (int i = 0; i<N; i++)
		array[i] = new int[N];
	{
		Timer t;
		int sum = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				sum += array[i][j];
	}
	{
		Timer t;
		int sum = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				sum += array[j][i];
	}
	for (int count = 0; count < N; count++) 
		delete[] array[count];
	delete[] array;
	return 0;
}
