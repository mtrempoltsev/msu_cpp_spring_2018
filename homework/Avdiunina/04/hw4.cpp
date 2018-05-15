//
// Created by polina997 on 3/16/18.
//
//
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
        Rows(int *arrptr, int lenght) : len(lenght)
        {
            //int *abc = arrptr;

            arr = new int [len];
            for(int i = 0; i < len; i++)
                arr[i] = *arrptr + i;
        }

        int& operator[](const int j)
        {
            if (0 <= j && j < len){
                return arr[j];
            }
            else
                throw std::out_of_range("");

        }

        ~Rows()
        {
            delete [] arr;
        }

    private:

        int len;
        int *arr;
    };

public:
         Matrix(int number_col, int number_rows): columns(number_col), rows(number_rows)
         {         //сразу присваиваем значения параметрам объекта, инициализируем матрицу

             array  = new int* [rows];
             for(int i = 0; i < rows; ++i)
                 array[i] = new int[columns];

         }

         ~Matrix()
         {                              //деструктор  if(array != nullptr) {} ??

             for (int i = 0; i < rows; ++i)
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
                 for (int i = 0; i < rows; ++i)
                     for (int j = 0; j < columns; ++j)
                         if (array[i][j] != other.array[i][j])
                             return false;
                 return true;
             }
         }

         bool operator !=(const Matrix& other) {                        //обратное действие равенству, сводим задачу к предыдущей
             return !(*this == other);
         }

         Matrix& operator *=(int number) {               //умножение на число поэлементно

             for (int i = 0; i < rows; ++i)
                 for (int j = 0; j < columns; ++j)
                     array[i][j] *= number;
         }

         Rows operator [](const int i){

             if (0 <= i && i < rows){
                 Rows c(array[i], columns);
                 return c;
             }
             else
                 throw std::out_of_range("");

         }

};

