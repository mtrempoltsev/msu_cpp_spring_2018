#include <iostream>

#include "matrix.cpp"

#define check(cond) do { if (!(cond)) std::cout << "line " << __LINE__ << ": " << #cond << '\n'; } while(0)

void do_testing() {
	Matrix A(3, 4);
	A[0][0] = 1; A[0][1] =  2; A[0][2] =  3; A[0][3] =  4;
	A[1][0] = 5; A[1][1] =  6; A[1][2] =  7; A[1][3] =  8;
	A[2][0] = 9; A[2][1] = 10; A[2][2] = 11; A[2][3] = 12;

	Matrix B(3, 4);
	B[0][0] = 1; B[0][1] =  2; B[0][2] =  3; B[0][3] =  4;
	B[1][0] = 5; B[1][1] =  6; B[1][2] =  7; B[1][3] =  8;
	B[2][0] = 9; B[2][1] = 10; B[2][2] = 11; B[2][3] = 12;

	check(A == B);

	check(A.nrows() == 3);
	check(A.ncols() == 4);

	check(A[0][0] == 1 && A[0][1] ==  2 && A[0][2] ==  3 && A[0][3] ==  4);
	check(A[1][0] == 5 && A[1][1] ==  6 && A[1][2] ==  7 && A[1][3] ==  8);
	check(A[2][0] == 9 && A[2][1] == 10 && A[2][2] == 11 && A[2][3] == 12);

	A[1][2] = -23;
	check(A[1][2] == -23);

	B[2][1] *= 2;
	check(B[2][1] == 20);

	std::vector<double> v = {1, 2, 3, 4};

	A *= v;

	check(A.nrows() == 3);
	check(A.ncols() == 1);

	check(A[0][0] ==  30);
	check(A[1][0] ==  -20);
	check(A[2][0] == 110);
}

int main() {
	do_testing();

	return 0;
}
