cmake_minimum_required(VERSION 3.15)
project(Ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ex1 main.cpp Matrix.cpp Activation.cpp Dense.cpp
        MlpNetwork.cpp)