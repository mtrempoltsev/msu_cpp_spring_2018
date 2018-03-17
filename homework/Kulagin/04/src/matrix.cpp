#pragma once

#include "../include/matrix.h"

// BEGIN-------------------------------------------------- GETTERS ----------------------------------------------------
ssize_t Matrix::nrows() const {
	return nrows_;
}

ssize_t Matrix::ncols() const {
	return ncols_;
}
// END---------------------------------------------------- GETTERS ----------------------------------------------------

// BEGIN-------------------------------------------------- OPERATORS --------------------------------------------------
bool Matrix::operator==(Matrix& _matrix) const {
	if (nrows_ != _matrix.nrows() || ncols_ != _matrix.ncols()) {
		return false;
	}

	for (ssize_t i = 0; i < nrows_; i++) {
		for (ssize_t j = 0; j < ncols_; j++) {
			if (data[i][j] != _matrix.data[i][j]) {
				return false;
			}
		}
	}

	return true;
}

bool Matrix::operator!=(Matrix& _matrix) const {
	return !(*this == _matrix);
}

MatrixRow& Matrix::operator[](const ssize_t nrow) {
	Assert(nrow >= 0 && nrow < nrows_);

	return data[nrow];
}

Matrix& Matrix::operator+=(const double k) {
	for (ssize_t i = 0; i < nrows_; i++) {
		for (ssize_t j = 0; j < ncols_; j++) {
			data[i][j] += k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator-=(const double k) {
	for (ssize_t i = 0; i < nrows_; i++) {
		for (ssize_t j = 0; j < ncols_; j++) {
			data[i][j] -= k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator*=(const double k) {
	for (ssize_t i = 0; i < nrows_; i++) {
		for (ssize_t j = 0; j < ncols_; j++) {
			data[i][j] *= k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator/=(const double k) {
	Assert(k != 0);

	for (ssize_t i = 0; i < nrows_; i++) {
		for (ssize_t j = 0; j < ncols_; j++) {
			data[i][j] /= k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator*=(const vector<double> v) {
	Assert(ncols_ == ssize_t(v.size()));

	Matrix _matrix(nrows_, 1);

	for (ssize_t i = 0; i < nrows_; i++) {
		double elem = 0;

		for (ssize_t j = 0; j < ncols_; j++) {
			elem += data[i][j] * v[j];
		}

		_matrix[i][0] = elem;
	}

	data.clear();

	return (*this = _matrix);
}
// END---------------------------------------------------- OPERATORS --------------------------------------------------

void Matrix::print() const {
	for (ssize_t i = 0; i < nrows_; i++) {
		for (ssize_t j = 0; j < ncols_; j++) {
			cout << data[i][j] << "\t";
		}

		cout << endl;
	}
}
