#include <iostream>
#include <chrono>

#define SIZE 10000

using namespace std;

class Timer
{
public:
	Timer() : start_(chrono::high_resolution_clock::now())
	{
	}

	~Timer()
	{
		const auto finish = chrono::high_resolution_clock::now();
		cout << chrono::duration_cast<chrono::microseconds>(finish - start_).count() << " us" << endl;
	}

private:
	const chrono::high_resolution_clock::time_point start_;
};

void sum_by_rows(int **m, int n) {
	Timer t;

	int sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum = sum + m[i][j];
		}
	}

}

int main(void)
{
	int** m = new int*[SIZE];
	for (int i = 0; i < SIZE; i++) {
		m[i] = new int[SIZE];
	}

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			m[i][j] = i + j;
		}
	}

	cout << "Time for rows: ";
	sum_by_rows(m, SIZE);

	for (int i = 0; i < SIZE; i++) {
		delete[] m[i];
	}

	delete[] m;

	return 0;
}