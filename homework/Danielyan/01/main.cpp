#include <chrono>
#include <iostream>
#include <vector>
#include <string>

const size_t row_count = 10000;
const size_t col_count = 10000;


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

using Row = std::vector<int>;

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::vector<Row> matrix(row_count, Row(col_count));
    for (auto& row : matrix) {
        for (int& elem : row) {
            elem = rand();
        }
    }

    int control_sum = 0;
    {
        Timer t;
	if (std::string(argv[1]) == "rows") {
            for (size_t i = 0; i < row_count; ++i)
	        for (size_t j = 0; j < col_count; ++j)
	       	    control_sum ^= matrix[i][j];
        } else if (std::string(argv[1]) == "cols") {
	    for (size_t j = 0; j < col_count; ++j)
                for (size_t i = 0; i < row_count; ++i)
	       	    control_sum ^= matrix[i][j];
        } else {
            std::cout << "Invalid argument " << argv[1] << std::endl;
            return 1;
	}
    }
    std::cout << control_sum << std::endl;
    return 0;
}

