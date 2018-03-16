#ifndef MATRIX_ROW_CPP
#define MATRIX_ROW_CPP

#include "../include/matrix_row.hpp"

// OPERATORS BEGINS
double& MatrixRow::operator[](const int _ncol) {
	if (_ncol < 0 || _ncol >= ncols) {
		cout << "Error: col index " << _ncol << " is out of range" << endl;

		exit(1);
	}

	return data[_ncol];
}

const double& MatrixRow::operator[](const int _ncol) const {
	if (_ncol < 0 || _ncol >= ncols) {
		cout << "Error: col index " << _ncol << " is out of range" << endl;

		exit(1);
	}

	return data[_ncol];
}
// OPERATORS ENDS

#endif
