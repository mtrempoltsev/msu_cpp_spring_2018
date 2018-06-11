using namespace std;
#include <iostream>

class Matrix
{
private:

    const int columns;
    const int rows;
    int** array;

    class Rows
    {
    public:
        Rows(int *arrstr, int length) : len(length), arr(arrstr)
        {
            //int *abc = arrptr;


        }

        int& operator[](const int j)
        {
            if (0 <= j && j < len)
            {
                return arr[j];
            }
            else
                throw std::out_of_range("");

        }


    private:

        int len;
        int *arr;
    };

public:
         Matrix(int number_col, int number_rows): columns(number_col), rows(number_rows)
         {         //сразу присваиваем значения параметрам объекта, инициализируем матрицу

             array  = new int* [columns];
             for(int i = 0; i < columns; ++i)
                 array[i] = new int[rows];

         }

         ~Matrix()
         {                              //деструктор  if(array != nullptr) {} ??

             for (int i = 0; i < columns; ++i)
                 delete [] array[i];

             delete [] array;
         }

         int getRows() const
         {                   //получаем количество строк

             return rows;
         }

         int getColumns() const
         {                   //получаем количество столбцов

             return columns;
         }


         bool operator ==(const Matrix& other) {                              //проверка на равенство поэлементно
             if (rows != other.getRows() || columns != other.getColumns()) {
                 return false;
             }
             else {
                 for (int i = 0; i < columns; ++i)
                     for (int j = 0; j < rows; ++j)
                         if (array[i][j] != other.array[i][j])
                             return false;
                 return true;
             }
         }

         bool operator !=(const Matrix& other) {                        //обратное действие равенству, сводим задачу к предыдущей
             return !(*this == other);
         }

         Matrix& operator *=(int number) {               //умножение на число поэлементно

             for (int i = 0; i < columns; ++i){
                 for (int j = 0; j < rows; ++j) {
                     array[i][j] *= number;
                 }
             }
             return *this;
         }

         Rows operator [](const int i){

             if (0 <= i && i < columns){
                 return Rows(array[i], rows);

             }
             else
                 throw std::out_of_range("");

         }

};
