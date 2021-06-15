#ifndef MATRIX_H
#define MATRIX_H

class Matrix 
{
public:
    Matrix(int rows, int cols);
    Matrix(float** array);
    Matrix(float **array, int rows, int cols);
    Matrix(){};
    ~Matrix();
    void Print();
    Matrix operator*(const Matrix& a);
    Matrix operator+(const Matrix& a);
    Matrix operator-(const Matrix& a);
    Matrix& operator=(const Matrix& a);
    const float Get(int row, int col) const;
    static Matrix &MultiplyElementwise(const Matrix& a, const Matrix& b);
    //Matrix operator.*();


    void Fill(int fill);
    void FillRandom(int min, int max);
    void Set(int row, int col, float value);

    int Rows();
    int Columns();

    float &At(int row, int col) const;
private:
    float** m_array;
    int m_rows{};
    int m_cols{};

};


#endif
