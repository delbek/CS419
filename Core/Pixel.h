//
// Created by delbek on 10/9/24.
//

#ifndef CS419_PIXEL_H
#define CS419_PIXEL_H

#include <cstdint>


struct Pixel
{
    Pixel() {}
    Pixel(uint8_t R, uint8_t G, uint8_t B): R(R), G(G), B(B) {}

    uint8_t R;
    uint8_t G;
    uint8_t B;
};


#endif //CS419_PIXEL_H
