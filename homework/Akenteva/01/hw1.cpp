#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer(const char *message): str(message), start_(std::chrono::high_resolution_clock::now()) {}

    ~Timer()
    {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << str << ' ' << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }


private:
    const char *str;
    const std::chrono::high_resolution_clock::time_point start_;
};


class int_2d_array
{
public:
    /* constructor: allocating memory and initialising the array */
    int_2d_array(size_t _rows, size_t _cols): rows(_rows), cols(_cols)
    {
        arr = (int **) malloc(sizeof(int *) * rows);
        for(size_t i = 0; i < rows; i++)
        {
            arr[i] = (int *) malloc(sizeof(int) * cols);
            // initialising (the exact numbers don't really matter)
            for(size_t j = 0; j < cols; j++)
                arr[i][j] = (int) (j + i * cols + 1) % 100;
        }
    }

    /* destructor: frees all the allocated memory */
    ~int_2d_array()
    {
        for(size_t i = 0; i < rows; i++)
            free(arr[i]);
        free(arr);
    }

    /* sums all the numbers; external cycle going through ROWS */
    int sum_by_rows()
    {
        int rez = 0;
        for(size_t i = 0; i < rows; i++)
            for(size_t j = 0; j < cols; j++)
                rez = rez + arr[i][j];
        return rez;
    }

    /* sums all the numbers; external cycle going through COLUMNS */
    int sum_by_cols()
    {
        int rez = 0;
        for (size_t j = 0; j < cols; j++)
            for(size_t i = 0; i < rows; i++)
                rez = rez + arr[i][j];
        return rez;
    }

private:
    size_t rows;
    size_t cols;
    int ** arr;
};




int main()
{    
    size_t const NUM_ROWS = 10000;
    size_t const NUM_COLS = 10000;
    int_2d_array a(NUM_ROWS, NUM_COLS);
    {
        Timer timer("BY ROWS   :");
        a.sum_by_rows();
    }

    {
        Timer timer("BY COLUMNS:");
        a.sum_by_cols();
    }
}