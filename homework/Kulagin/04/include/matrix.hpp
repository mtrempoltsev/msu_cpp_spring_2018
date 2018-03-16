#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../src/matrix_row.cpp"

using namespace std;


class Matrix {

public:
	// CONSTRUCTOR BEGINS
	Matrix(int _nrows, int _ncols) : nrows(_nrows), ncols(_ncols) {
		if (nrows <= 0) {
			cout << "Error: cannot initialize matrix with " << nrows << " rows" << endl;

			exit(1);
		}

		if (ncols <= 0) {
			cout << "Error: cannot initialize matrix with " << ncols << " columns" << endl;

			exit(1);
		}

		for (int i = 0; i < nrows; i++) {
			data.push_back(MatrixRow(ncols));
		}
	}
	// CONSTRUCTOR ENDS

	// GETTERS BEGINS
	int get_nrows() const;
	int get_ncols() const;
	// GETTERS ENDS

	// OPERATORS BEGINS
	bool operator==(Matrix&) const;
	bool operator!=(Matrix&) const;

	MatrixRow& operator[](int _nrow);

	Matrix& operator+=(const double k);

	Matrix& operator-=(const double k);

	Matrix& operator*=(const double k);
	Matrix& operator*=(const std::vector<double>);

	Matrix& operator/=(const double k);
	// OPERATORS ENDS

	void print() const;

	// DESTRUCTOR BEGINS
	~Matrix() {
		data.clear();
	};
	// DESTRUCTOR ENDS

private:
	int nrows;
	int ncols;

	vector<MatrixRow> data;
};

#endif
