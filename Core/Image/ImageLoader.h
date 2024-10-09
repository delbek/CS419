//
// Created by delbek on 10/9/24.
//

#ifndef CS419_IMAGELOADER_H
#define CS419_IMAGELOADER_H

#include <string>
#include "Image.h"
#include <vector>


class ImageLoader
{
public:
    Image loadImage(std::string imagePath);
    std::vector<Image> loadMultipleImages(std::vector<std::string> imagePaths);
};


#endif //CS419_IMAGELOADER_H
