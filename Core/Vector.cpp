//
// Created by delbek on 10/9/24.
//

#include "Vector.h"
#include <stdexcept>
#include <cstring>


Vector::Vector(unsigned size)
:   m_Size(size)
{
    m_Data = new double[size];
}

Vector::Vector(const Vector &otherVector)
:   m_Size(otherVector.m_Size)
{
    m_Data = new double[m_Size];
    memcpy(m_Data, otherVector.m_Data, sizeof(double) * m_Size);
}

Vector &Vector::operator=(const Vector &otherVector)
{
    if (this == &otherVector)
    {
        return *this;
    }
    free();

    m_Size = otherVector.m_Size;
    m_Data = new double[m_Size];
    memcpy(m_Data, otherVector.m_Data, sizeof(double) * m_Size);

    return *this;
}

Vector::Vector(Vector &&otherVector)
:   m_Size(otherVector.m_Size)
{
    m_Data = otherVector.m_Data;
    otherVector.m_Data = nullptr;
}

Vector &Vector::operator=(Vector &&otherVector)
{
    if (this == &otherVector)
    {
        return *this;
    }
    free();

    m_Size = otherVector.m_Size;
    m_Data = otherVector.m_Data;

    otherVector.m_Data = nullptr;

    return *this;
}

void Vector::free()
{
    delete[] m_Data;
}

Vector::~Vector()
{
    this->free();
}

double Vector::operator[](unsigned index) const
{
    if (index >= m_Size)
    {
        throw std::out_of_range("You are trying to access the out-of-bonds of the vector.");
    }
    return m_Data[index];
}

double &Vector::operator[](unsigned index)
{
    if (index >= m_Size)
    {
        throw std::out_of_range("You are trying to access the out-of-bonds of the vector.");
    }
    return m_Data[index];
}
