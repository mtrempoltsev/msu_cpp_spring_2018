#include <iostream>

#include "src/matrix.cpp"


void do_testing() {
	Matrix A(3, 4);
	A[0][0] = 1; A[0][1] =  2; A[0][2] =  3; A[0][3] =  4;
	A[1][0] = 5; A[1][1] =  6; A[1][2] =  7; A[1][3] =  8;
	A[2][0] = 9; A[2][1] = 10; A[2][2] = 11; A[2][3] = 12;

	Matrix B(3, 4);
	B[0][0] = 1; B[0][1] =  2; B[0][2] =  3; B[0][3] =  4;
	B[1][0] = 5; B[1][1] =  6; B[1][2] =  7; B[1][3] =  8;
	B[2][0] = 9; B[2][1] = 10; B[2][2] = 11; B[2][3] = 12;

	is_ok(A == B, "A != B", __FILE__, __LINE__);

	is_ok(A.nrows() == 3, "A.nrows() == 3", __FILE__, __LINE__);
	is_ok(A.ncols() == 4, "A.ncols() == 4", __FILE__, __LINE__);

	is_ok(A[0][0] == 1 && A[0][1] ==  2 && A[0][2] ==  3 && A[0][3] ==  4, "fill matrix error", __FILE__, __LINE__);
	is_ok(A[1][0] == 5 && A[1][1] ==  6 && A[1][2] ==  7 && A[1][3] ==  8, "fill matrix error", __FILE__, __LINE__);
	is_ok(A[2][0] == 9 && A[2][1] == 10 && A[2][2] == 11 && A[2][3] == 12, "fill matrix error", __FILE__, __LINE__);

	A[1][2] = -3;
	is_ok(A[1][2] == -3, "A[1][2] == -3", __FILE__, __LINE__);

	B[2][1] *= 2;
	is_ok(B[2][1] == 20, "B[2][1] == 20", __FILE__, __LINE__);

	vector<double> v = {1, 2, 3, 4};

	A *= v;

	is_ok(A.nrows() == 3, "A.nrows() == 3", __FILE__, __LINE__);
	is_ok(A.ncols() == 1, "A.ncols() == 1", __FILE__, __LINE__);

	is_ok(A[0][0] ==  30, "A[0][0] ==  30", __FILE__, __LINE__);
	is_ok(A[1][0] ==  40, "A[1][0] ==  40", __FILE__, __LINE__);
	is_ok(A[2][0] == 110, "A[2][0] == 110", __FILE__, __LINE__);
}

int main() {
	do_testing();

	return 0;
}
