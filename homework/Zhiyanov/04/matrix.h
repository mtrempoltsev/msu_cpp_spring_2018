#pragma once
#include <stdexcept>

class Matrix{
public:
	class Array{
	public:
		Array(int *tarr, int tsize) : arr(tarr), size(tsize){};

		~Array(){}

		int& operator[](int ind){
			if (ind >= size)
				throw std::out_of_range("");
			return arr[ind];
		}

		const int& operator[](int ind) const{
			if (ind >= size)
				throw std::out_of_range("");

			return arr[ind];
		}	

	private:
		int size;
		int *arr;
    };

	Matrix(const int trows, const int tcols) :
		  rows(trows), cols(tcols){
		this->arr = new int[cols * rows];
	}

	~Matrix(){
		delete [] arr;
	}

	int getColumns() const{
		return rows;
	}

	int getRows() const{
		return cols;
	}

	bool operator==(const Matrix& other) const{
        if (rows != other.getColumns() || 
        	cols != other.getRows())
        	return false;
        
        for (int i = 0; i < rows; ++i)
        	for (int j = 0; j < cols; ++j)
        		if (arr[i * cols + j] != other[i][j])
        			return false;

        return true;
    }

    bool operator!=(const Matrix& other) const{
    	if (rows != other.getColumns() || 
        	cols != other.getRows())
        	return true;
        
        for (int i = 0; i < rows; ++i)
        	for (int j = 0; j < cols; ++j)
        		if (arr[i * cols + j] != other[i][j])
        			return true;

        return false;
    }

    Matrix& operator*=(int num){
    	for (int i = 0; i < rows; ++i)
    		for (int j = 0; j < cols; ++j)
    			arr[i * cols + j] *= num; 

    	return *this;
    }

    const Array operator[](int ind) const{
    	if (ind >= rows)
    		throw std::out_of_range("");
    	const Array tmp_arr(arr + ind * cols, cols);
    	return tmp_arr;
    }

    Array operator[](int ind){
    	if (ind >= rows)
    		throw std::out_of_range("");
    	Array tmp_arr(arr + ind * cols, cols);
    	return tmp_arr;
    }

private:
	int cols;
	int rows;
	int *arr;
};