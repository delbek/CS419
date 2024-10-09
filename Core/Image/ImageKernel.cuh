//
// Created by delbek on 10/9/24.
//

#ifndef CS419_IMAGEKERNEL_CUH
#define CS419_IMAGEKERNEL_CUH

#include "Input.cuh"
#include "Output.cuh"
#include <vector>
#include <string>


class ImageKernel
{
public:
    ImageKernel(std::string kernelName): m_KernelName(kernelName) {}

    Output* runKernel(Input* input);
    virtual Output* hostFunction(Input* input) = 0;

private:
    std::string m_KernelName;
};


#endif //CS419_IMAGEKERNEL_CUH
