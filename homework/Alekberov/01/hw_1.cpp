
#include <chrono>
#include <iostream>

class Timer {
public:
  Timer ()
    : start_ (std::chrono::high_resolution_clock::now ()) {
  }

  ~Timer () {
    const auto finish = std::chrono::high_resolution_clock::now ();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds> (finish - start_).count () << " us" << std::endl;
  }

private:
  const std::chrono::high_resolution_clock::time_point start_;
};

void sum_rows (int ** ary, int rows, int col, long long * sum) {
  *sum = 0;
  std::cout << "time - sum by rows: " << "\n";
  Timer time;
  for (int i = 0; i < rows; i++) {
    int *b = ary[i];
    for (int j = 0; j < col; j++) {
      (*sum) += b[j];
    }
  }
}

void sum_col (int ** ary, int rows, int col, long long * sum) {
  *sum = 0;
  std::cout << "time - sum by col: " << "\n";
  Timer time;
  for (int i = 0; i < col; i++) {
    for (int j = 0; j < rows; j++) {
      (*sum) += ary[j][i];
    }
  }
}

int main () {
  int rows = 10000;
  int col = 5000;
  long long sum = 0;

  int** ary = (int**)malloc ((rows * sizeof (int*)));
  for (int i = 0; i < rows; i++) {
    ary[i] = (int*)malloc (col * sizeof (int));
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < col; j++) {
      ary[i][j] = i + j;
    }
  }

  sum_rows (ary, rows, col, &sum);
  std::cout << "sum = " << sum << "\n";
  sum_col (ary, rows, col, &sum);
  std::cout << "sum = " << sum << "\n";

  for (int i = 0; i < rows; i++) {
    free (ary[i]);
  }
  free (ary);

  system ("pause");
  return 0;
}


