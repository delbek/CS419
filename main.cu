#include "ImageLoader.h"
#include "Visualizer.h"


int main()
{
    ImageLoader loader;
    Visualizer visualizer;

    Image image = loader.loadImage("/home/delbek/CS419/SampleImages/example-24bpp.bmp");
    visualizer.generateHTMLFile(
            "/home/delbek/CS419/GeneratedHTMLs/file",
            {image, image}, {"image1", "image2"}
    );

    return 0;
}
