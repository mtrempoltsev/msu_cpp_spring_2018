#include <iostream>
#include "timer.h"

int** malloc_matrix(int m, int n) {
    int** matrix = (int**)malloc((m * sizeof(int*))
                                 + (m * (n * sizeof(int))));
    for (int i = 0; i < m; ++i) {
        matrix[i] = (int *)(matrix + m) + i * n;
    }
    return matrix;
}
void matrix_init(int** matrix, int n, int  m) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            matrix[i][j] = 2;
        }
    }
}
int64_t sum_row_matrix(int n, int m) {
    int** matrix = malloc_matrix(n, m);
    matrix_init(matrix, n, m);
    int64_t sum_matrix = 0;
    Timer t("sum_row_matrix");
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            sum_matrix += matrix[i][j];
        }
    }
    free(matrix);
    return sum_matrix;
}
int main() {
    int n = 10000,
            m = 10000;
    cout <<"sum_row_matrix(n, m) = "
         << sum_row_matrix(n, m)
         << endl;
    return 0;
}
