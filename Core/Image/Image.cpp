//
// Created by delbek on 10/9/24.
//

#include "Image.h"
#include <stdexcept>
#include <cstring>


Image::Image(unsigned height, unsigned width)
:   m_Height(height),
    m_Width(width)
{
    m_Matrix = new Pixel[m_Height * m_Width];
}

Image::Image(const Image &otherImage)
:   m_Height(otherImage.m_Height),
    m_Width(otherImage.m_Width)
{
    unsigned gridSize = m_Height * m_Width;
    m_Matrix = new Pixel[gridSize];
    memcpy(m_Matrix, otherImage.m_Matrix, sizeof(Pixel) * gridSize);
}

Image &Image::operator=(const Image &otherImage)
{
    if (this == &otherImage)
    {
        return *this;
    }
    free();

    m_Height = otherImage.m_Height;
    m_Width = otherImage.m_Width;

    unsigned gridSize = m_Height * m_Width;
    m_Matrix = new Pixel[gridSize];
    memcpy(m_Matrix, otherImage.m_Matrix, sizeof(Pixel) * gridSize);

    return *this;
}

Image::Image(Image &&otherImage)
:   m_Height(otherImage.m_Height),
    m_Width(otherImage.m_Width)
{
    m_Matrix = otherImage.m_Matrix;

    otherImage.m_Matrix = nullptr;
}

Image &Image::operator=(Image &&otherImage)
{
    if (this == &otherImage)
    {
        return *this;
    }
    free();

    m_Height = otherImage.m_Height;
    m_Width = otherImage.m_Width;
    m_Matrix = otherImage.m_Matrix;

    otherImage.m_Matrix = nullptr;

    return *this;
}

void Image::free()
{
    delete[] m_Matrix;
}

Image::~Image()
{
    this->free();
}

Pixel Image::operator[](unsigned int index) const
{
    if (index >= this->gridSize())
    {
        throw std::out_of_range("You are trying to access the out-of-bonds of the image matrix.");
    }
    return m_Matrix[index];
}

Pixel &Image::operator[](unsigned int index)
{
    if (index >= this->gridSize())
    {
        throw std::out_of_range("You are trying to access the out-of-bonds of the image matrix.");
    }
    return m_Matrix[index];
}
