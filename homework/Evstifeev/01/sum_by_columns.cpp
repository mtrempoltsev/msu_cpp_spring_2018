#include <iostream>
#include <chrono>
using namespace std;

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
      std::cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << "us" <<std::endl;
    }

private:
  const std::chrono::high_resolution_clock::time_point start_;
};

int** init_matrix(int n, int m)
{
        int **matrix = new int*[n];
        for (size_t i = 0; i < n; i++) {
                matrix[i] = new int[m];
                for (size_t j = 0; j < m; j++) {
                        matrix[i][j] = 1;
                }
        }
        return matrix;
}

int main()
{
        const size_t ROW_NUM = 10001; // Кол-во строк
        const size_t COLUMN_NUM = 10000; // Кол-во столбцов
        long long sum = 0;

        int **matrix = init_matrix(ROW_NUM, COLUMN_NUM);
        {
                Timer t;
                for (size_t i = 0; i < COLUMN_NUM; i++) {
                        for (size_t j = 0; j < ROW_NUM; j++) {
                                sum += matrix[j][i];
                        }
                }
        }
        std::cout << "Sum by columns: " << sum << std::endl;
        for (size_t i = 0; i < ROW_NUM; i++) {
                delete [] matrix[i];
        }
        delete [] matrix;
        return 0;
}
