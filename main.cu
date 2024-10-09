#include "ImageLoader.h"
#include "Visualizer.h"
#include "AffineTransformation.cuh"


int main()
{
    ImageLoader loader;
    Visualizer visualizer;

    std::vector<Image> images = std::move(loader.loadMultipleImages({
        "/home/delbek/CS419/SampleImages/example-24bpp.bmp"
    }));

    Matrix matrix(3, 3);
    matrix[0] = 0; matrix[1] = -1; matrix[2] = images[0].getWidth() - 1; matrix[3] = 1; matrix[4] = 0; matrix[5] = 0; matrix[6] = 0; matrix[7] = 0; matrix[8] = 1;

    AffineTransformation affineTransformation;
    affineTransformation.applyAffineTransformation(images[0], matrix);

    visualizer.generateHTMLFile(
            "/home/delbek/CS419/GeneratedHTMLs/file",
            images, {"image"}
    );

    return 0;
}
