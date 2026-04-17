cmake_minimum_required(VERSION 3.18)

project(nbody_cuda_simulation LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

add_executable(nbody_cuda src/main.cu)

target_compile_options(nbody_cuda PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-O3 -use_fast_math>)