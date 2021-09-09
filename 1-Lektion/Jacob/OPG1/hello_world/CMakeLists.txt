cmake_minimum_required(VERSION 3.5)
project(hello_world LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(hello_world main.cpp)
target_link_libraries(hello_world ${OpenCV_LIBS})
