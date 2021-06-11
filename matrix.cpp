#include "matrix.h"

#include <iostream>

Matrix::Matrix(int rows, int cols): m_rows(rows), m_cols(cols) {
    //pointer to pointer, to the element at row 1, column 1
    m_array = new float*[rows];
    //for each row, create an array with size equal to number of elements in a column
    for(int i = 0; i < rows; i++) {
        m_array[i] = new float[cols];
    }
}


Matrix::~Matrix() {
    //delete rows
    for (int i = 0; i < m_rows; ++i) {
        delete[] m_array[i];
    }
    //delete the pointer
    delete[] m_array;    
}


void Matrix::Print() {
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            std::cout << m_array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}