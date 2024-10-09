//
// Created by delbek on 10/9/24.
//

#ifndef CS419_IMAGE_H
#define CS419_IMAGE_H

#include "Pixel.h"
#include <cstdint>


// row-major
class Image
{
public:
    Image(unsigned height, unsigned width);
    Image(const Image& otherImage);
    Image& operator=(const Image& otherImage);
    Image(Image&& otherImage);
    Image& operator=(Image&& otherImage);
    void free();
    ~Image();

    Pixel operator[](unsigned index) const;
    Pixel& operator[](unsigned index);
    __inline__ unsigned getHeight() const {return m_Height;}
    __inline__ unsigned getWidth() const {return m_Width;}
    __inline__ unsigned gridSize() const {return m_Height * m_Width;}
    __inline__ unsigned getSize() const {return this->gridSize() * sizeof(Pixel);}
    __inline__ Pixel* getImage() const {return m_Data;}

    void applyPermutation(unsigned* permutation);

private:
    Pixel* m_Data;
    unsigned m_Height;
    unsigned m_Width;
};


#endif //CS419_IMAGE_H
