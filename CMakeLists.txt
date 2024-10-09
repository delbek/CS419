cmake_minimum_required(VERSION 3.27)
project(CS419)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler ${OpenMP_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include(CheckLanguage)
check_language(CUDA)
if(CMAKE_CUDA_COMPILER)
    set(CMAKE_CUDA_ARCHITECTURES 70)
    enable_language(CUDA)
    add_definitions(-DGPU_AVAILABLE)
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --ptxas-options=-v -Xcompiler ${OpenMP_CXX_FLAGS}")
    find_package(CUDAToolkit REQUIRED)
endif()

include_directories(.)
include_directories(Core)
include_directories(Visualization)
include_directories(Point_Processing)
include_directories(Core/Image)
include_directories(Core/FileFormats)
include_directories(SampleImages)
include_directories(GeneratedHTMLs)

add_executable(CS419
        Core/Image/Image.cpp
        Core/Image/Image.h
        Visualization/Visualizer.cpp
        Visualization/Visualizer.h
        Core/Image/ImageKernel.cu
        Core/Image/ImageKernel.cuh
        Core/Image/ImageLoader.cpp
        Core/Image/ImageLoader.h
        Core/FileFormats/bmpread.h
        Core/FileFormats/bmpread.c
        Point_Processing/ImageSubtraction.cu
        Point_Processing/ImageSubtraction.cuh
        main.cu)

target_link_libraries(CS419
        OpenMP::OpenMP_CXX
        cuda
        CUDA::cudart
        ${CUDA_LIBRARIES}
)

target_compile_options(CS419 PRIVATE -O3)
target_compile_options(CS419 PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
        -O3
        --generate-line-info
        >)
