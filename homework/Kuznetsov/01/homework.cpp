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

int x[10000][10000];
int main() {
	{
		Timer t;
		int count = 0;
		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < 10000; j++) {
				count += x[i][j];
			}
		}
		std::cout << "Po strokam : ";
	}
	{
		Timer t;
		int count = 0;
		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < 10000; j++) {
				count += x[j][i];
			}
		}
		std::cout << "Po stolbcam : ";
	}
	
	int in;
	std::cin >> in;
	return 0;
}