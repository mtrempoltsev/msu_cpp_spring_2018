#include "timer.h"

int** malloc_matrix(int m, int n) {
    int** matrix = (int**)malloc((m * sizeof(int*))
                                 + (m * (n * sizeof(int))));
    for (int i = 0; i < m; ++i) {
        matrix[i] = (int *)(matrix + m) + i * n;
    }
    return matrix;
}
void matrix_init(int** matrix, int m, int  n) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            matrix[i][j] = 2;
        }
    }
}
int64_t sum_row_matrix(int m, int n) {
    int** matrix = malloc_matrix(m, n);
    matrix_init(matrix, m, n);
    int64_t sum_matrix = 0;
    Timer t;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            sum_matrix += matrix[i][j];
        }
    }
    free(matrix);
    return sum_matrix;
}
int main() {
    int n = 10000,
            m = 20000;
    std::cout <<"sum_row_matrix(m, n) = "
         << sum_row_matrix(m, n)
         << std::endl;
    return 0;
}
