#pragma once

#include "../include/matrix.hpp"

// GETTERS BEGINS
size_t Matrix::get_nrows() const {
	return nrows;
}

size_t Matrix::get_ncols() const {
	return ncols;
}
// GETTERS ENDS

// OPERATORS BEGINS
bool Matrix::operator==(Matrix& _matrix) const {
	if (nrows != _matrix.nrows || ncols != _matrix.ncols) {
		return false;
	}

	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
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

MatrixRow& Matrix::operator[](const size_t _nrow) {
	if (_nrow < 0 || _nrow >= nrows) {
		cout << "Error: row index " << _nrow << " is out of range" << endl;

		exit(1);
	}

	return data[_nrow];
}

Matrix& Matrix::operator+=(const double k) {
	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
			data[i][j] += k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator-=(const double k) {
	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
			data[i][j] -= k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator*=(const double k) {
	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
			data[i][j] *= k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator/=(const double k) {
	if (k == 0) {
		cout << "Error: division by zero" << endl;

		exit(1);
	}

	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
			data[i][j] /= k;
		}
	}

	return (*this);
}

Matrix& Matrix::operator*=(const vector<double> v) {
	if (ncols != v.size()) {
		cout << "Error: cannot multiply matrix by vector (size mismatch)" << endl;

		exit(1);
	}

	Matrix _matrix(nrows, 1);

	for (size_t i = 0; i < nrows; i++) {
		double elem = 0;

		for (size_t j = 0; j < ncols; j++) {
			elem += data[i][j] * v[j];
		}

		_matrix[i][0] = elem;
	}

	data.clear();

	return (*this = _matrix);
}
// OPERATORS ENDS(

void Matrix::print() const {
	for (size_t i = 0; i < nrows; i++) {
		for (size_t j = 0; j < ncols; j++) {
			cout << data[i][j] << "\t";
		}

		cout << endl;
	}
}
