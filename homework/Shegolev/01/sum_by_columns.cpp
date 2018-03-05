#include "header.h"
#include "bench_param.h"

void sum_by_columns (int **array, int size) {
	Timer t;
	volatile int sum = 0;
	
	for (int j = 0; j < size; ++j) {
		for (int i = 0; i < size; ++i) {
			sum += array[i][j];
		}
	}
}

int main() {
	std::cout << "size," << "attempt," << "by_columns" << std::endl;
	
	// heating
	recursive_fibonacci(fibonacci_number);
	
	// iterate by array size
	for (int size = 16; size <= max_size; size += (int) (double) max_size / number_of_steps + 0.5) {
		// array initialization
		int **array = new int* [size];
		for (int i = 0; i < size; ++i) {
			array[i] = new int [size];
		}
		
		// several attempts under the same conditions
		for (int attempt = 1; attempt <= number_of_attempts; ++attempt) {
			// (re)initialization by numbers
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					array[i][j] = rand() % 10 + 1;
				}
			}
			// benchmark
			std::cout << size << "," << attempt << ",";
			sum_by_columns(array, size);
			std::cout << std::endl;
		}
		
		// clearing memory
		for (int i = 0; i < size; ++i) {
			delete [] array[i];
		}
		delete [] array;
	}
	return 0;
}


