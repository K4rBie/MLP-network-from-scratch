#ifndef MATRIX_H
#define MATRIX_H

#include "CImg.h"

using cimg_library::CImg;

class Matrix 
{
public:
    Matrix(int rows, int cols);
    Matrix(float** array);
    Matrix(float **array, int rows, int cols);
    Matrix(const CImg<float>& image);
    Matrix(){};
    ~Matrix();
    Matrix(const Matrix& a);

    Matrix& operator*(const Matrix& a);
    Matrix& operator+(const Matrix& a);
    Matrix& operator-(const Matrix& a) const;
    Matrix& operator=(const Matrix& a);
    const float Get(int row, int col) const;
    static Matrix &MultiplyElementwise(const Matrix& a, const Matrix& b);
    //Matrix operator.*();


    void Fill(int fill);
    void FillRandom(int min, int max);
    void Set(int row, int col, float value);
    float &at(int row, int col) const;

    int rows() const;
    int columns() const;

    void print()const ;


private:
    float** m_array = nullptr;
    int m_rows{};
    int m_cols{};

};


#endif
