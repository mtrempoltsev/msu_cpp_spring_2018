#include <chrono>
#include <iostream>
#include <ctime>

enum {MATR_SIZE = 10000};

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

void fill_matrix(int **matrix, int rows, int columns) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = 1 + rand() % 100;
		}
	}
}

void print_matrix(int **matrix, int rows, int columns) {

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << matrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

void sum_columns(int **matrix, int rows, int columns) {
	
	volatile int sum = 0;
	Timer t;

	for (int j = 0; j < columns; j++) {
		for (int i = 0; i < rows; i++) {
			sum += matrix[i][j];
		}
	}
}

void sum_rows(int **matrix, int rows, int columns) {

		volatile int sum = 0;
		Timer t;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				sum += matrix[i][j];
			}
		}
}

int main() {

	int **matr1 = new int * [MATR_SIZE];	

	for (int i = 0; i < MATR_SIZE; i++) {
		matr1[i] = new int [MATR_SIZE];
	}

	srand(time(NULL));

	fill_matrix(matr1, MATR_SIZE, MATR_SIZE);
	// print_matrix(matr1, MATR_SIZE, MATR_SIZE);
	
	sum_rows(matr1, MATR_SIZE, MATR_SIZE);
	sum_columns(matr1, MATR_SIZE, MATR_SIZE);

	for (int i = 0; i < MATR_SIZE; i++) {
		delete [] matr1[i];
	}
	delete [] matr1;
		
	return 0;
}
