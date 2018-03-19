#pragma once

#include "matrix_row.cpp"

class Matrix {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Matrix(ssize_t nrows, ssize_t ncols) : nrows_(nrows), ncols_(ncols) {
		Assert(nrows > 0);
		Assert(ncols > 0);

		for (ssize_t i = 0; i < nrows_; i++) {
			data.push_back(MatrixRow(ncols_));
		}
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	ssize_t nrows() const;
	ssize_t ncols() const;
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- OPERATORS --------------------------------------------------
	bool operator==(Matrix&) const;
	bool operator!=(Matrix&) const;

	MatrixRow& operator[](const ssize_t nrow);
	const MatrixRow& operator[](const ssize_t nrow) const;

	Matrix& operator+=(const double k);

	Matrix& operator-=(const double k);

	Matrix& operator*=(const double k);
	Matrix& operator*=(const std::vector<double>&);

	Matrix& operator/=(const double k);
	// END------------------------------------------------ OPERATORS --------------------------------------------------

	void print() const;

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Matrix() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	ssize_t nrows_;
	ssize_t ncols_;

	std::vector<MatrixRow> data;
};
