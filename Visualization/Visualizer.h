//
// Created by delbek on 10/9/24.
//

#ifndef CS419_VISUALIZER_H
#define CS419_VISUALIZER_H

#include <vector>
#include "Image.h"
#include <string>


class Visualizer
{
public:
    void generateHTMLFile(std::string filename, const std::vector<Image>& images, std::vector<std::string> displayNames);

private:
    std::string rgbToHex(Pixel pixel);
};


#endif //CS419_VISUALIZER_H
