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
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " ms" << std::endl;
    }

private:
    const std::chrono::high_resolution_clock::time_point start_;
};


int main(){
	const size_t size = 10000;
	int **matrix = new int *[size];

	for(size_t i = 0; i < size; ++i){
		matrix[i] = new int [size];
	}
	for(size_t i = 0; i < size; ++i){
		for(size_t j = 0; j < size; ++j){
			matrix[i][j] = i + j;
		}
	}

	volatile long int sum = 0;
	{
		Timer t_rows;
		for(size_t i = 0; i < size; ++i){
			for(size_t j = 0; j < size; ++j){
				sum += matrix[i][j];
			}
		}
	}

	for(size_t i = 0; i < size; ++i){
		delete[] matrix[i];
	}
	delete[] matrix;
	return 0;
} 
