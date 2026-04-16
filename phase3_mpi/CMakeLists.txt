cmake_minimum_required(VERSION 3.10)
project(nbody_mpi_simulation)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(nbody_mpi src/main.cpp)

target_link_libraries(nbody_mpi PRIVATE MPI::MPI_CXX)
target_compile_options(nbody_mpi PRIVATE -O3)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")