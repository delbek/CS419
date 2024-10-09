//
// Created by delbek on 10/9/24.
//

#include "Matrix.h"
#include <stdexcept>
#include <cstring>


Matrix::Matrix(unsigned int row, unsigned int col)
:   m_Row(row),
    m_Col(col)
{
    m_Data = new double[m_Row * m_Col];
}

Matrix::Matrix(const Matrix &otherMatrix)
:   m_Row(otherMatrix.m_Row),
    m_Col(otherMatrix.m_Col)
{
    m_Data = new double[m_Row * m_Col];
    memcpy(m_Data, otherMatrix.m_Data, sizeof(double) * m_Row * m_Col);
}

Matrix &Matrix::operator=(const Matrix &otherMatrix)
{
    if (this == &otherMatrix)
    {
        return *this;
    }
    free();

    m_Row = otherMatrix.m_Row;
    m_Col = otherMatrix.m_Col;
    m_Data = new double[m_Row * m_Col];
    memcpy(m_Data, otherMatrix.m_Data, sizeof(double) * m_Row * m_Col);

    return *this;
}

Matrix::Matrix(Matrix &&otherMatrix)
:   m_Row(otherMatrix.m_Row),
    m_Col(otherMatrix.m_Col)
{
    m_Data = otherMatrix.m_Data;
    otherMatrix.m_Data = nullptr;
}

Matrix &Matrix::operator=(Matrix &&otherMatrix)
{
    if (this == &otherMatrix)
    {
        return *this;
    }
    free();

    m_Row = otherMatrix.m_Row;
    m_Col = otherMatrix.m_Col;

    m_Data = otherMatrix.m_Data;
    otherMatrix.m_Data = nullptr;

    return *this;
}

void Matrix::free()
{
    delete[] m_Data;
}

Matrix::~Matrix()
{
    this->free();
}

double Matrix::operator[](unsigned int index) const
{
    if (index >= (m_Row * m_Col))
    {
        throw std::out_of_range("You are trying to access the out-of-bonds of the matrix.");
    }
    return m_Data[index];
}

double &Matrix::operator[](unsigned int index)
{
    if (index >= (m_Row * m_Col))
    {
        throw std::out_of_range("You are trying to access the out-of-bonds of the matrix.");
    }
    return m_Data[index];
}

std::vector<Matrix> Matrix::DLUDecomposition() const
{
    std::vector<Matrix> dlu(3, {m_Row, m_Col});

    for (int i = 0; i < m_Row; ++i)
    {
        for (int j = 0; j < m_Col; ++j)
        {
            if (i == j)
            {
                dlu[0][i * m_Col + j] = m_Data[i * m_Col + j];
            }
            else if (i > j)
            {
                dlu[1][i * m_Col + j] = m_Data[i * m_Col + j];
            }
            else if (i < j)
            {
                dlu[2][i * m_Col + j] = m_Data[i * m_Col + j];
            }
        }
    }

    return dlu;
}

Matrix Matrix::getColMajor() const
{
    Matrix colMajor(m_Col, m_Row);

    for (int i = 0; i < m_Row; ++i)
    {
        for (int j = 0; j < m_Col; ++j)
        {
            colMajor[j * m_Row + i] = m_Data[i * m_Col + j];
        }
    }

    return colMajor;
}
