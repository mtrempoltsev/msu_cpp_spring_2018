#include <chrono>
#include <iostream>

using std::endl;

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
	int **matrix = new int *[10000];

	for(int i = 0; i < 10000; ++i){
		matrix[i] = new int [10000];
	}
	for(int i = 0; i < 10000; ++i){
		for(int j = 0; j < 10000; ++j){
			matrix[i][j] = i + j;
		}
	}

	volatile long unsigned int sum = 0;
	{
		Timer t_rows;
		for(int j = 0; j < 10000; ++j){
			for(int i = 0; i < 10000; ++i){
				sum += matrix[i][j];
			}
		}
	}

	for(int i = 0; i < 10000; ++i){
		delete[] matrix[i];
	}
	delete[] matrix;
	return 0;
} 

