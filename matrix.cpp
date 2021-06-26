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

    m_array = new float*[m_rows];

    //for each row, create an array with size equal to number of elements in a column
    for(int i = 0; i < m_rows; i++) {
        m_array[i] = new float[m_cols];
    }

    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_array[i][j] = array[i][j];
        }
    }
}

Matrix::Matrix(float **array, int rows, int cols): m_rows(rows), m_cols(cols)
{
    m_array = array;
}

Matrix::Matrix(const CImg<float> &image)
{
    m_rows = image.height();
    m_cols = image.width();

    m_array = new float*[m_rows];

    //for each row, create an array with size equal to number of elements in a column
    for(int i = 0; i < m_rows; i++) {
        m_array[i] = new float[m_cols];
    }

    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_array[i][j] = (image(i,j) - 127.5) / 127.5;
        }
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

Matrix::Matrix(const Matrix &a)
{
    if (m_array != nullptr) {
        //delete old array
        for (int i = 0; i < m_rows; ++i) {
            delete[] m_array[i];
        }
        delete[] m_array;
    }


    m_rows = a.m_rows;
    m_cols = a.m_cols;

    //create new array
    m_array = new float*[m_rows];
    for(int i = 0; i < m_rows; i++) {
        m_array[i] = new float[m_cols];
    }

    //assign new values
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_array[i][j] = a.at(i, j);
        }
    }
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

int Matrix::rows() const
{
    return m_rows;
}

int Matrix::columns() const
{
    return m_cols;
}

void Matrix::print() const
{
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            std::cout << m_array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix &Matrix::operator*(const Matrix &a)
{
    int i, j, k;
    int r1 = this->rows();
    int c1 = this->columns();
    int r2 = a.rows();
    int c2 = a.columns();

    Matrix* ret = new Matrix(r1, c2);
    ret->Fill(0);
    float** product = ret->m_array;

    float** e = this->m_array;
    float** f = a.m_array;


    if (c1 != r2) {
          throw std::invalid_argument("Matrices cannot be multiplied.");
    } else {
        for(i=0; i<r1; ++i)
        for(j=0; j<c2; ++j)
        for(k=0; k<c1; ++k)
        {
            product[i][j] += e[i][k] * f[k][j];
        }
    }

    return *ret;
}

Matrix &Matrix::operator+(const Matrix &a)
{
    Matrix* ret = new Matrix(a.m_rows, a.m_cols);

    for(int i = 0; i < ret->m_rows; i++) {
        for(int j = 0; j < ret->m_cols; j++) {
            ret->m_array[i][j] = this->at(i, j) + a.at(i, j);
        }
    }

    return *ret;
}

Matrix &Matrix::operator-(const Matrix &a) const
{
    Matrix* ret = new Matrix(a.m_rows, a.m_cols);

    for(int i = 0; i < ret->m_rows; i++) {
        for(int j = 0; j < ret->m_cols; j++) {
            ret->m_array[i][j] = this->at(i, j) - a.at(i, j);
        }
    }

    return *ret;
}


Matrix& Matrix::operator=( Matrix const &a)
{
    if (m_array != nullptr) {
        //delete old array
        for (int i = 0; i < m_rows; ++i) {
            delete[] m_array[i];
        }
        delete[] m_array;
    }


    m_rows = a.m_rows;
    m_cols = a.m_cols;

    //create new array
    m_array = new float*[m_rows];
    for(int i = 0; i < m_rows; i++) {
        m_array[i] = new float[m_cols];
    }

    //assign new values
    for(int i = 0; i < m_rows; i++) {
        for(int j = 0; j < m_cols; j++) {
            m_array[i][j] = a.at(i, j);
        }
    }

    return * this;
}


const float Matrix::Get(int row, int col) const
{
    return m_array[row][col];
}

void Matrix::Set(int row, int col, float value)
{
    m_array[row][col] = value;
}

float& Matrix::at(int row, int col) const
{
    float** row_ptr = m_array + row;
    float* elem = *row_ptr + col;
    return *elem;
}

Matrix& Matrix::MultiplyElementwise(const Matrix &a, const Matrix &b)
{
    if (a.m_cols != b.m_cols || a.m_rows != b.m_rows) throw;

    auto* ret = new Matrix(a.m_rows, a.m_cols);

    for(int i = 0; i < ret->rows(); i++) {
        for(int j = 0; j < ret->columns(); j++) {
            ret->m_array[i][j] = a.Get(i, j) * b.Get(i, j);
        }
    }

    return *ret;
}
