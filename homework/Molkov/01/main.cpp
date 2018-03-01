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

int main() {
	int rows = 10000;
	int col = 10000;

	int** arr = (int**)malloc((rows * sizeof(int*)));
	for (int i = 0; i < rows; i++) {
		arr[i] = (int*)malloc(col * sizeof(int));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < col; j++) {
			arr[i][j] = i + j;
		}
	}

	// sum by rows
	long long res = 0;
	{
		std::cout << "time - sum by rows: " << "\n";
		Timer time;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < col; j++) {
				res += arr[i][j];
			}
		}
	}
	std::cout << "res = " << res << "\n";

	// sum by col
	{
		res = 0;
		std::cout << "time - sum by columns: " << "\n";
		Timer time;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < col; j++) {
				res += arr[j][i];
			}
		}
	}
	std::cout << "res = " << res << "\n";

	for (int i = 0; i < rows; i++) {
		free(arr[i]);
	}
	free(arr);

	//system("pause");
	return 0;
}