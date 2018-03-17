#include <chrono>
#include <iostream>

const int SIZE = 10000;

class Timer{
    public:
        Timer():start_(std::chrono::high_resolution_clock::now()){}

        void get_time()
        {
            const auto finish = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
        }
    
    private:
        const std::chrono::high_resolution_clock::time_point start_;
};

int main(){
	int **arr = new int*[SIZE];
	for (int i = 0; i < SIZE; ++i)
		arr[i] = new int[SIZE];

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			arr[i][j] = (i + j) % 19;

	long int sum = 0;

	Timer timer;

	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			sum += arr[j][i];

	timer.get_time();

	for (int i = 0; i < SIZE; ++i)
		delete [] arr[i];
	delete[] arr;

	return 0;
}