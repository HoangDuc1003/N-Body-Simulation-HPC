cmake_minimum_required(VERSION 3.10)
project(NBodySim)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")


add_executable(nbody_sim main.cpp)