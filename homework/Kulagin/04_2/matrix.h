#pragma once

#include <vector>
#include <stdexcept>

class MatrixRow {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	MatrixRow(size_t ncols): ncols_(ncols) {
		if (ncols_ == 0) {
			throw std::out_of_range("");
		}

		data.resize(ncols_);
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- OPERATORS --------------------------------------------------
	double& operator[](const size_t ncol) {
		if (ncol >= ncols_) {
			throw std::out_of_range("");
		}

		return data[ncol];
	}

	const double& operator[](const size_t ncol) const {
		if (ncol >= ncols_) {
			throw std::out_of_range("");
		}

		return data[ncol];
	}
	// END------------------------------------------------ OPERATORS --------------------------------------------------


	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~MatrixRow() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	std::vector<double> data;

	size_t ncols_;
};


class Matrix {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Matrix(size_t ncols, size_t nrows) : nrows_(nrows), ncols_(ncols) {
		for (size_t i = 0; i < ncols_; i++) {
			data.push_back(MatrixRow(nrows_));
		}
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	size_t getRows() const {
		return nrows_;
	}
	size_t getColumns() const {
		return ncols_;
	}
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- OPERATORS --------------------------------------------------
	bool operator==(const Matrix& _matrix) const {
		if (nrows_ != _matrix.getRows() || ncols_ != _matrix.getColumns()) {
			return false;
		}

		for (size_t i = 0; i < ncols_; i++) {
			for (size_t j = 0; j < nrows_; j++) {
				if (data[i][j] != _matrix.data[i][j]) {
					return false;
				}
			}
		}

		return true;
	}

	bool operator!=(Matrix& _matrix) const {
		return !operator==(_matrix);
	}

	MatrixRow& operator[](const size_t ncol) {
		if (ncol >= ncols_) {
			throw std::out_of_range("");
		}

		return data[ncol];
	}

	const MatrixRow& operator[](const size_t ncol) const {
		if (ncol >= ncols_) {
			throw std::out_of_range("");
		}

		return data[ncol];
	}

	Matrix& operator+=(const double k) {
		for (size_t i = 0; i < nrows_; i++) {
			for (size_t j = 0; j < ncols_; j++) {
				data[i][j] += k;
			}
		}

		return (*this);
	}

	Matrix& operator-=(const double k) {
		for (size_t i = 0; i < nrows_; i++) {
			for (size_t j = 0; j < ncols_; j++) {
				data[i][j] -= k;
			}
		}

		return (*this);
	}

	Matrix& operator*=(const double k) {
		for (size_t i = 0; i < ncols_; i++) {
			for (size_t j = 0; j < nrows_; j++) {
				data[i][j] *= k;
			}
		}

		return (*this);
	}
	Matrix& operator*=(const std::vector<double>& v) {
		if (ncols_ != v.size()) {
			throw std::out_of_range("");
		}

		Matrix _matrix(nrows_, 1);

		for (size_t i = 0; i < nrows_; i++) {
			double elem = 0;

			for (size_t j = 0; j < ncols_; j++) {
				elem += data[i][j] * v[j];
			}

			_matrix[i][0] = elem;
		}

		data.clear();

		return (*this = _matrix);
	}

	Matrix& operator/=(const double k) {
		if (k == 0) {
			throw std::logic_error("Division by zero!");
		}

		for (size_t i = 0; i < nrows_; i++) {
			for (size_t j = 0; j < ncols_; j++) {
				data[i][j] /= k;
			}
		}

		return (*this);
	}
	// END------------------------------------------------ OPERATORS --------------------------------------------------

	void print() const;

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Matrix() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	size_t nrows_;
	size_t ncols_;

	std::vector<MatrixRow> data;
};
