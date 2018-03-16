#pragma once

#include "../include/matrix_row.h"

// BEGIN---------------------------------------- OPERATORS ------------------------------------------------------------
double& MatrixRow::operator[](const ssize_t ncol) {
	Assert(ncol >= 0 && ncol < ncols_, "col index " + to_string(ncol) + " is out of range", __FILE__, __LINE__);

	return data[ncol];
}

const double& MatrixRow::operator[](const ssize_t ncol) const {
	Assert(ncol >= 0 && ncol < ncols_, "col index " + to_string(ncol) + " is out of range", __FILE__, __LINE__);

	return data[ncol];
}
// END------------------------------------------ OPERATORS ------------------------------------------------------------
