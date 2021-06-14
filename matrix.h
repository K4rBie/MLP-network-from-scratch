#ifndef MATRIX_H
#define MATRIX_H

template <class T>
class Matrix 
{
public:
    Matrix(int rows, int cols);
    ~Matrix();
    void Print();
    Matrix<T> operator*(const Matrix<T>& a);
    Matrix<T> operator+(const Matrix<T>& a);
    Matrix<T> operator-(const Matrix<T>& a);
    static Matrix MultiplyElementwise(const Matrix<T>& a, const Matrix<T>& b);
    //Matrix operator.*();


private:
    T** m_array;
    int m_rows{};
    int m_cols{};

};


#endif