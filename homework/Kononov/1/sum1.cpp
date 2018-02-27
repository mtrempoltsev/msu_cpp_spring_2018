//Kononov Sergey group BD-11

#include <chrono>
#include <iostream>

class Timer
{
	public:
		Timer():start_(std::chrono::high_resolution_clock::now())
		{}

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
	Timer t;
	const int DIM = 10000;

	int** array = new int * [DIM];

	int sum = 0;

	for (int j = 0; j < DIM; ++j)
		array[j] = new int [DIM];

	for (int j = 0; j < DIM; ++j)
		for (int i = 0; i < DIM; ++i)
			array[i][j] = 0;
	
	for (int j = 0; j < DIM; ++j)
		for (int i = 0; i < DIM; ++i)
			sum += array[j][i];
	
	for (int i = 0; i < DIM; ++i)
		delete [] array[i];

	delete [] array;
	
	return 0;
}
