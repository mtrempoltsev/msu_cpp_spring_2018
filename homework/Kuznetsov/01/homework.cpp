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
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
	}

private:
	const std::chrono::high_resolution_clock::time_point start_;
};

const size_t RANGE = 10000;
int main() {
	int **x = new int*[RANGE];
	for (size_t i = 0; i < RANGE; i++) {
		x[i] = new int[RANGE];
	}
	{
		Timer t;
		volatile int count = 0;
		for (size_t i = 0; i < RANGE; i++) {
			for (size_t j = 0; j < RANGE; j++) {
				count += x[i][j];
			}
		}
		std::cout << "Po strokam : ";
	}
	{
		Timer t;
		volatile int count = 0;
		for (size_t i = 0; i < RANGE; i++) {
			for (size_t j = 0; j < RANGE; j++) {
				count += x[j][i];
			}
		}
		std::cout << "Po stolbcam : ";
	}

	for (size_t i = 0; i < RANGE; i++) {
		delete[] x[i];
	}
	delete[] x;

	return 0;
}