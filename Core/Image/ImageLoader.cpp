//
// Created by delbek on 10/9/24.
//

#include "ImageLoader.h"
#include <iostream>
#include "bmpread.h"


Image ImageLoader::loadImage(std::string imagePath)
{
    bmpread_t bmp;
    unsigned int flags = 0;
    flags |= BMPREAD_TOP_DOWN;

    if(!bmpread(imagePath.c_str(), flags, &bmp))
    {
        throw std::runtime_error("Could not open file: " + imagePath);
    }

    unsigned width = bmp.width;
    unsigned height = bmp.height;
    Image image(height, width);

    unsigned gridSize = image.gridSize();
    auto data = bmp.data;
    for (unsigned i = 0; i < gridSize; ++i)
    {
        Pixel pixel;
        pixel.R = data[i * 3];
        pixel.G = data[i * 3 + 1];
        pixel.B = data[i * 3 + 2];
        image[i] = pixel;
    }

    bmpread_free(&bmp);

    return image;
}

std::vector<Image> ImageLoader::loadMultipleImages(std::vector<std::string> imagePaths)
{
    std::vector<Image> images;

#pragma omp parallel for num_threads(imagePaths.size()) schedule(dynamic, 1)
    for (int i = 0; i < imagePaths.size(); ++i)
    {
        const Image& image = loadImage(imagePaths[i]);
        #pragma omp critical
        {
            images.emplace_back(image);
        }
    }

    return images;
}
