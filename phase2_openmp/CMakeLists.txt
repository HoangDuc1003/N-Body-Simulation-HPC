cmake_minimum_required(VERSION 3.10)
project(NBodySim)

find_package(OpenMP REQUIRED)

add_executable(nbody_sim_2 src/main.cpp)

target_compile_options(nbody_sim_2 PRIVATE -O3)
target_link_libraries(nbody_sim_2 PRIVATE OpenMP::OpenMP_CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
