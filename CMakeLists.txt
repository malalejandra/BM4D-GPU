cmake_minimum_required(VERSION 3.8..3.16)
project(bm4d-gpu LANGUAGES CXX CUDA)

## Add support for C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)

find_package(OpenCV REQUIRED core video videoio highgui)

set(CXX
    src/allreader.cpp
    src/bm4d.cpp
    src/main.cpp
    )
set(CU  src/kernels.cu)
set(H
    include/bm4d-gpu/allreader.h
    include/bm4d-gpu/bm4d.h
    include/bm4d-gpu/helper_cuda.h
    include/bm4d-gpu/helper_string.h
    include/bm4d-gpu/kernels.cuh
    include/bm4d-gpu/parameters.h
    include/bm4d-gpu/stopwatch.hpp
    include/bm4d-gpu/utils.h
    )

add_executable(bm4d-gpu ${CXX} ${CU} ${H})
target_link_libraries(bm4d-gpu ${OpenCV_LIBRARIES})
target_include_directories(bm4d-gpu PUBLIC include)
target_include_directories(bm4d-gpu PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(bm4d-gpu PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
