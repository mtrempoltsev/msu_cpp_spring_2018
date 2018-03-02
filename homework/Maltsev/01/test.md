n = 10000
m = 20000
Test 1:
829249 us
sum_col_matrix(n, m) = 400000000
484097 us
sum_row_matrix(n, m) = 400000000
Test 2:
821336 us
sum_col_matrix(n, m) = 400000000
490819 us
sum_row_matrix(n, m) = 400000000
Test 3:
838477 us
sum_col_matrix(n, m) = 400000000
498216 us
sum_row_matrix(n, m) = 400000000
Test 4:
838357 us
sum_col_matrix(n, m) = 400000000
493835 us
sum_row_matrix(n, m) = 400000000
Test 5:
825142 us
sum_col_matrix(n, m) = 400000000
494053 us
sum_row_matrix(n, m) = 400000000
Test 6:
832718 us
sum_col_matrix(n, m) = 400000000
491205 us
sum_row_matrix(n, m) = 400000000

Видна явная разница во времени, так как в памяти элементы в строке находятся рядом, а при суммировании по столбцам происходят скачки в памяти.
