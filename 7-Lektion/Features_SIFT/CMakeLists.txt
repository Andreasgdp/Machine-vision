cmake_minimum_required(VERSION 3.5)

project(Features_SIFT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(openCV_DIR /home/jacob/opencv_build/opencv/build)

add_executable(Features_SIFT main.cpp)

cmake_minimum_required(VERSION 3.5)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Features_SIFT  ${OpenCV_LIBS})
