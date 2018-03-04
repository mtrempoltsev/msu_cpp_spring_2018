#include <chrono>
#include <iostream>

namespace options
{
	constexpr size_t numberOfRows = 10000;
	constexpr size_t numberOfColumns = 10000;
}

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
	//Memory allocation
	int** matrix = new int*[options::numberOfRows];
	for (size_t i = 0; i < options::numberOfRows; i++)
		matrix[i] = new int[options::numberOfColumns];
	int sum = 0;
	//By Rows
	{
		std::cout << "By rows: ";
		Timer t;
		for (size_t i = 0; i < options::numberOfRows; i++)
			for (size_t j = 0; j < options::numberOfColumns; j++)
				sum += matrix[i][j];
	}
	sum = 0;
	//By Columns
	{
		std::cout << "By columns: ";
		Timer t;
		for (size_t j = 0; j < options::numberOfColumns; j++)
			for (size_t i = 0; i < options::numberOfRows; i++)
				sum += matrix[i][j];
	}
	//Memory cleaning
	for (size_t i = 0; i < options::numberOfRows; i++)
		delete[] matrix[i];
	delete[] matrix;
	return 0;
}
