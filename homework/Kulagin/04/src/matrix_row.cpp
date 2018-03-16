#pragma once

#include "../include/matrix_row.h"

// BEGIN---------------------------------------- OPERATORS ------------------------------------------------------------
double& MatrixRow::operator[](const int ncol) {
	Assert(ncol >= 0 && ncol < ncols_, "Error: col index " + to_string(ncol) + " is out of range", __FILE__, __LINE__);

	return data[ncol];
}

const double& MatrixRow::operator[](const int ncol) const {
	Assert(ncol >= 0 && ncol < ncols_, "Error: col index " + to_string(ncol) + " is out of range", __FILE__, __LINE__);

	return data[ncol];
}
// END------------------------------------------ OPERATORS ------------------------------------------------------------
