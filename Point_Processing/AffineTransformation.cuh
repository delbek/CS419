//
// Created by delbek on 10/9/24.
//

#ifndef CS419_AFFINETRANSFORMATION_CUH
#define CS419_AFFINETRANSFORMATION_CUH

#include "Matrix.h"
#include "Image.h"
#include <string>


class AffineTransformation
{
public:
    Matrix estimateAffineTransformation(unsigned* referencePoints, unsigned* controlPoints, unsigned numberOfPoints);
    void applyAffineTransformation(Image& image, const Matrix& transformationMatrix);
};


#endif //CS419_AFFINETRANSFORMATION_CUH
