//
// Created by delbek on 10/9/24.
//

#include "ImageKernel.cuh"
#include "omp.h"
#include <iostream>


Output *ImageKernel::runKernel(Input *input)
{
    auto start = omp_get_wtime();
    this->hostFunction(input);
    auto end = omp_get_wtime();

    std::cout << "Entire execution of the " + m_KernelName + " took: " << end - start << " seconds." << std::endl;
}
