#pragma once

#include "../src/matrix_row.cpp"

using namespace std;


class Matrix {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Matrix(size_t _nrows, size_t _ncols) : nrows(_nrows), ncols(_ncols) {
		if (nrows <= 0) {
			cout << "Error: cannot initialize matrix with " << nrows << " rows" << endl;

			exit(1);
		}

		if (ncols <= 0) {
			cout << "Error: cannot initialize matrix with " << ncols << " columns" << endl;

			exit(1);
		}

		for (size_t i = 0; i < nrows; i++) {
			data.push_back(MatrixRow(ncols));
		}
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	size_t get_nrows() const;
	size_t get_ncols() const;
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- OPERATORS --------------------------------------------------
	bool operator==(Matrix&) const;
	bool operator!=(Matrix&) const;

	MatrixRow& operator[](size_t _nrow);

	Matrix& operator+=(const double k);

	Matrix& operator-=(const double k);

	Matrix& operator*=(const double k);
	Matrix& operator*=(const std::vector<double>);

	Matrix& operator/=(const double k);
	// END------------------------------------------------ OPERATORS --------------------------------------------------


	void print() const;

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Matrix() {
		data.clear();
	};
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	size_t nrows;
	size_t ncols;

	vector<MatrixRow> data;
};
