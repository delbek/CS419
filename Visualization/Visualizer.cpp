//
// Created by delbek on 10/9/24.
//

#include "Visualizer.h"
#include <iostream>
#include <fstream>


std::string Visualizer::rgbToHex(Pixel pixel)
{
    char hexCol[8];
    snprintf(hexCol, sizeof(hexCol), "#%02x%02x%02x", pixel.R, pixel.G, pixel.B);
    return {hexCol};
}

void Visualizer::generateHTMLFile(std::string filename, const std::vector<Image>& images, std::vector<std::string> displayNames)
{
    filename += ".html";
    std::ofstream html(filename);

    html << "<!DOCTYPE html>\n";
    html << "<html lang=\"en\">\n";
    html << "<head>\n";
    html << "<meta charset=\"UTF-8\">\n";
    html << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    html << "<title>Multiple Image Gallery</title>\n";
    html << "<style>\n";
    html << ".pixel { width: 1px; height: 1px; float: left; }\n";
    html << ".clear { clear: both; }\n";
    html << ".image-container { margin-bottom: 20px; }\n";
    html << "</style>\n";
    html << "</head>\n";
    html << "<body>\n";
    html << "<h1>Image Gallery</h1>\n";

    for (int iter = 0; iter < images.size(); ++iter)
    {
        const Image& image = images[iter];
        html << "<div class=\"image-container\">\n";
        html << "<h2>" << displayNames[iter] << "</h2>\n";

        for (int i = 0; i < image.getHeight(); ++i)
        {
            for (int j = 0; j < image.getWidth(); ++j)
            {
                Pixel pixel = image[i * image.getHeight() + j];
                html << "<div class=\"pixel\" style=\"background-color:" << rgbToHex(pixel) << ";\"></div>\n";
            }
            html << "<div class=\"clear\"></div>\n";
        }

        html << "</div>\n";
    }

    html << "</body>\n";
    html << "</html>\n";

    html.close();
}
