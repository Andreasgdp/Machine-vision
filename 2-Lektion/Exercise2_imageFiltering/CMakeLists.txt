cmake_minimum_required(VERSION 3.5)

project(Exercise2_imageFiltering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Exercise2_imageFiltering main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Exercise2_imageFiltering  ${OpenCV_LIBS})
