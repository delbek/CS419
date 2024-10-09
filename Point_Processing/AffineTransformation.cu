//
// Created by delbek on 10/9/24.
//

#include "AffineTransformation.cuh"
#include "DeviceKernels.cuh"
#include "GPUHelpers.cuh"
#include "Vector.h"
#include <cusolverDn.h>


__global__ void applyTransformation(double* matrix, unsigned* permutation, unsigned row, unsigned col)
{
    unsigned totalThreadCount = blockDim.x * gridDim.x;
    unsigned threadID = blockDim.x * blockIdx.x + threadIdx.x;

    unsigned gridSize = row * col;
    unsigned chunkSize = (gridSize + totalThreadCount - 1) / totalThreadCount;
    unsigned start = threadID * chunkSize;
    unsigned end = min((threadID + 1) * chunkSize, gridSize);

    for (unsigned iter = start; iter < end; ++iter)
    {
        unsigned i = iter / col;
        unsigned j = iter % col;

        int new_i = matrix[0] * i + matrix[1] * j + matrix[2];
        int new_j = matrix[3] * i + matrix[4] * j + matrix[5];
        new_i = max(0, min(new_i, row - 1));
        new_j = max(0, min(new_j, col - 1));

        unsigned new_index = new_i * col + new_j;
        permutation[iter] = new_index;
    }
}

__global__ void jacobi(double* A, double* x, double* b)
{

}

void AffineTransformation::applyAffineTransformation(Image &image, const Matrix &transformationMatrix)
{
    unsigned gridSize = image.gridSize();
    unsigned* permutation = new unsigned[gridSize];
    for (int i = 0; i < gridSize; ++i) permutation[i] = i;

    unsigned* d_permutation;
    cudaMalloc(&d_permutation, sizeof(unsigned) * gridSize);
    cudaMemcpy(d_permutation, permutation, sizeof(unsigned) * gridSize, cudaMemcpyHostToDevice);

    double* d_matrix;
    cudaMalloc(&d_matrix, sizeof(double) * 3 * 3);
    cudaMemcpy(d_matrix, transformationMatrix.getMatrix(), sizeof(double) * 3 * 3, cudaMemcpyHostToDevice);

    int gridDimension;
    int blockDimension;
    cudaOccupancyMaxPotentialBlockSizeVariableSMem(
        &gridDimension,
        &blockDimension,
        applyTransformation,
        noShared,
        0);

    applyTransformation<<<gridDimension, blockDimension>>>(d_matrix, d_permutation, image.getHeight(), image.getWidth());
    cudaDeviceSynchronize();

    cudaMemcpy(permutation, d_permutation, sizeof(unsigned) * gridSize, cudaMemcpyDeviceToHost);
    image.applyPermutation(permutation);

    cudaFree(d_permutation);
    cudaFree(d_matrix);
    delete[] permutation;
}

Matrix AffineTransformation::estimateAffineTransformation(unsigned int* referencePoints, unsigned int* controlPoints, unsigned int numberOfPoints)
{
    Vector b(numberOfPoints * 2);
    for (unsigned int i = 0; i < numberOfPoints * 2; ++i)
    {
        b[i] = static_cast<double>(referencePoints[i]);
    }

    Matrix A(numberOfPoints * 2, 6);
    for (unsigned int i = 0; i < numberOfPoints; ++i)
    {
        A[i * 2 * 6 + 0] = controlPoints[i * 2];
        A[i * 2 * 6 + 1] = controlPoints[i * 2 + 1];
        A[i * 2 * 6 + 2] = 1.0;
        A[i * 2 * 6 + 3] = 0.0;
        A[i * 2 * 6 + 4] = 0.0;
        A[i * 2 * 6 + 5] = 0.0;

        A[(i * 2 + 1) * 6 + 0] = 0.0;
        A[(i * 2 + 1) * 6 + 1] = 0.0;
        A[(i * 2 + 1) * 6 + 2] = 0.0;
        A[(i * 2 + 1) * 6 + 3] = controlPoints[i * 2];
        A[(i * 2 + 1) * 6 + 4] = controlPoints[i * 2 + 1];
        A[(i * 2 + 1) * 6 + 5] = 1.0;
    }
    A = std::move(A.getColMajor());

    double* h_x = new double[6];
    double* d_A, * d_b, * d_x;

    // to be completed

    Matrix affineMatrix(3, 3);
    affineMatrix[0] = h_x[0];  // a11
    affineMatrix[1] = h_x[1];  // a12
    affineMatrix[2] = h_x[2];  // tx
    affineMatrix[3] = h_x[3];  // a21
    affineMatrix[4] = h_x[4];  // a22
    affineMatrix[5] = h_x[5];  // ty
    affineMatrix[6] = 0.0;     // last row is [0 0 1]
    affineMatrix[7] = 0.0;
    affineMatrix[8] = 1.0;

    delete[] h_x;

    return affineMatrix;
}
