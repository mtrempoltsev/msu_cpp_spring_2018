#ifndef MATRIX_H__
#define MATRIX_H__
#include <stdio.h>
#include <stdint.h>
#include <stdexcept>
class MatrixCol
{
	private:
	int32_t *data_;
	int32_t r_;
	public:
	MatrixCol(int32_t *data, uint32_t size);
	~MatrixCol();
	const int32_t& operator[](uint32_t offset) const;
	int32_t& operator[](uint32_t offset);
}; //proxy-class
class Matrix
{
	private:
	int32_t *data_;
	uint32_t r_;
	uint32_t c_;
	public:
	Matrix();
	Matrix(const uint32_t c, const uint32_t r);
	Matrix(const Matrix&);
	~Matrix();
	Matrix& operator*=(int32_t a);
	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;
	uint32_t getColumns() const;
	uint32_t getRows() const;
	const MatrixCol operator[](uint32_t offset) const;
	MatrixCol operator[](uint32_t offset);
	/*operator [][]*/
};
/*matrix-row methods*/
MatrixCol::MatrixCol(int32_t *data, uint32_t size)
{
	data_=data;
	r_=size;
}
MatrixCol::~MatrixCol()
{
}
const int32_t& MatrixCol::operator[](uint32_t offset) const
{
	if(offset>=r_)
	{
		throw std::out_of_range("");
	}
	return data_[offset];
}
int32_t& MatrixCol::operator[](uint32_t offset)
{
	if(offset>=r_)
	{
		throw std::out_of_range("");
	}
	return data_[offset];
}
Matrix::Matrix(): data_(0), r_(0), c_(0)
{}
Matrix::Matrix(const uint32_t c, const uint32_t r): r_(r), c_(c)
{
	data_=new int32_t[r*c];
}
Matrix::~Matrix()
{
	delete []data_;
}
Matrix::Matrix(const Matrix& m): r_(m.r_), c_(m.c_)
{
	data_=new int32_t[r_*c_];
	for(uint32_t i=0; i<r_*c_; i++)
	{
		data_[i]=m.data_[i];
	}
}
Matrix& Matrix::operator*=(int32_t a)
{
	for(uint32_t i=0; i<r_*c_; i++)
	{
		data_[i]*=a;
	}
	return *this;
}
bool Matrix::operator==(const Matrix &m) const
{
	if(r_!=m.r_)
	{
		return false;
	}
	if(c_!=m.c_)
	{
		return false;
	}
	for(uint32_t i=0; i<r_*c_; i++)
	{
		if(data_[i]!=m.data_[i])
		{
			return false;
		}
	}
	return true;
}
bool Matrix::operator!=(const Matrix &m) const
{
	return !(*this==m);
}
uint32_t Matrix::getColumns() const
{
	return c_;
}
uint32_t Matrix::getRows() const
{
	return r_;
}
const MatrixCol Matrix::operator[](uint32_t offset) const
{
	if(offset>=c_)
	{
		throw std::out_of_range("");
	}
	return MatrixCol(data_+offset*r_, r_);
}
MatrixCol Matrix::operator[](uint32_t offset)
{
	if(offset>=c_)
	{
		throw std::out_of_range("");
	}
	return MatrixCol(data_+offset*r_, r_);
}
#endif
