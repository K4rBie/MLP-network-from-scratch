#ifndef MATRIX_H
#define MATRIX_H

class Matrix 
{
public:
    Matrix(int rows, int cols);
    ~Matrix();
    void Print();
    Matrix operator*();
    //Matrix operator.*();


private:
    float ** m_array;
    int m_rows{};
    int m_cols{};

};


#endif