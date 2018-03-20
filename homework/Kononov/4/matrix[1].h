//Kononov Sergey BD-11

#include <iostream>

class Vector{
	private:
		int size;
		int * vector = nullptr;
	public:
		Vector(int * p_matrix, int vect_size):vector(p_matrix), size(vect_size){};
			
		int operator[](int pos) const{
			if ((pos < size) && (pos >= 0))
				return vector[pos];
			else
				throw  std::out_of_range("");
		};

		int & operator[](int pos){
			if ((pos < size) && (pos >= 0))
				return vector[pos];
			else
				throw  std::out_of_range("");
		};
};



class Matrix{
	private:
		int row_n, col_n; 
		int ** matrix = nullptr;
	public:
		Matrix(int col_num = 1, int row_num = 1): row_n(row_num), col_n(col_num){
				if(( row_num < 0) || (col_num < 0))
					throw std::out_of_range("");

				//Create matrix
				matrix = new int * [col_n];
				for (int j = 0; j < col_n; j++)
					matrix[j] = new int[row_n];
				
				//Fill matrix with zeroes
				for (int j = 0; j < col_n; j++)
					for (int i = 0; i < row_n; i++ )
						matrix[j][i] = 0;
		};

		~Matrix(){
			for (int j = 0; j < col_n; j++)
				delete [] matrix[j];

			delete [] matrix;
		}

		friend std::ostream & operator<<(std::ostream & out, const Matrix & m);

		int getRows() const{
			return row_n;	
		};

		int getColumns() const{
			return col_n;
		};

		const Vector operator[](int pos) const{
			if ((pos < col_n) && (pos >= 0))
				return Vector(matrix[pos], row_n);
			else
				throw std::out_of_range("");
		};

		Vector operator[](int pos){
			if ((pos < col_n) && (pos >= 0))
				return Vector(matrix[pos], row_n);
			else
				throw std::out_of_range("");
		};

		bool operator==(const Matrix & other) const{
			
			//Check object addresses
			if (this == & other)
				return true;
		
			//Check matrix dimension
			if ((other.getColumns() != col_n) || (other.getRows() != row_n)) 
				return false;

			//Check each element
			for (int i = 0; i < col_n; i++)
				for (int j = 0; j < row_n; j++)
					if (matrix[i][j] != other[i][j])
						return false;

			return true;
		};

		bool operator!=(const Matrix & other) const{
			
			//Apply == operator to objects
			if (*this == other)
				return false;
			
			return true;
		};

		void operator*=(int value){
			for (int i = 0; i < col_n; i++)
				for (int j = 0; j < row_n; j++)
					matrix[i][j] *= value;
		};
};

std::ostream & operator<<(std::ostream & out, const Matrix & m){
			for (int i = 0; i < m.getRows(); i++)
			{
				for (int j = 0; j < m.getColumns(); j++)
					out  << m[j][i] << " ";

				out << std::endl;
			};
			return out;
};
