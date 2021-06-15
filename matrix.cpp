#include "matrix.h"

#include <iostream>
#include <algorithm>


Matrix::Matrix(int rows, int cols): m_rows(rows), m_cols(cols)
{
    //pointer to pointer, to the element at row 1, column 1
    m_array = new float*[rows];

    //for each row, create an array with size equal to number of elements in a column
    for(int i = 0; i < rows; i++) {
        m_array[i] = new float[cols];
    }
}

Matrix::Matrix(float **array)
{
    m_array = array;
    int size = sizeof(m_array)/sizeof(m_array[0]);
    m_rows = size;
    m_cols = 1;
}

Matrix::Matrix(float **array, int rows, int cols): m_rows(rows), m_cols(cols)
{
    m_array = array;
}


Matrix::~Matrix() {
    //delete rows
    for (int i = 0; i < m_rows; ++i) {
        delete[] m_array[i];
    }
    //delete the pointer
    delete[] m_array;    
}

void Matrix::Fill(int fill) {
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_array[i][j] = fill;
        }
    }
}

void Matrix::FillRandom(int min, int max) {
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_array[i][j] = min + (float)std::rand()/(float)RAND_MAX*(max - min);
        }
    }
}

void Matrix::Print() {
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            std::cout << m_array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix& Matrix::operator=( Matrix const &a)
{
    Matrix* ret = new Matrix(a.m_rows, a.m_cols);

    for(int i = 0; i < ret->m_rows; i++) {
        for(int j = 0; j < ret->m_cols; j++) {
            ret->m_array[i][j] = a.At(i, j);
        }
    }

    return *ret;
}

const float Matrix::Get(int row, int col) const
{
    return m_array[row][col];
}

void Matrix::Set(int row, int col, float value)
{
    m_array[row][col] = value;
}

float& Matrix::At(int row, int col) const
{
    float** row_ptr = m_array + row;
    float* elem = *row_ptr + col;
    return *elem;
}

int Matrix::Rows()
{
    return m_rows;
}

int Matrix::Columns()
{
    return m_cols;
}

Matrix& Matrix::MultiplyElementwise(const Matrix &a, const Matrix &b)
{
    if (a.m_cols != b.m_cols || a.m_rows != b.m_rows) throw;

    auto* ret = new Matrix(a.m_rows, a.m_cols);

    for(int i = 0; i < ret->Rows(); i++) {
        for(int j = 0; j < ret->Columns(); j++) {
            ret->m_array[i][j] = a.Get(i, j) * b.Get(i, j);
        }
    }

    return *ret;
}
