//
// Created by delbek on 10/9/24.
//

#ifndef CS419_MATRIX_H
#define CS419_MATRIX_H

#include <vector>


// row-major
class Matrix
{
public:
    Matrix(unsigned row, unsigned col);
    Matrix(const Matrix& otherMatrix);
    Matrix& operator=(const Matrix& otherMatrix);
    Matrix(Matrix&& otherMatrix);
    Matrix& operator=(Matrix&& otherMatrix);
    void free();
    ~Matrix();

    double operator[](unsigned index) const;
    double& operator[](unsigned index);
    __inline__ unsigned getRow() const {return m_Row;}
    __inline__ unsigned getCol() const {return m_Col;}
    __inline__ double* getMatrix() const {return m_Data;}
    [[nodiscard]] Matrix getColMajor() const;

    [[nodiscard]] std::vector<Matrix> DLUDecomposition() const;

private:
    unsigned m_Row;
    unsigned m_Col;
    double* m_Data;
};


#endif //CS419_MATRIX_H
