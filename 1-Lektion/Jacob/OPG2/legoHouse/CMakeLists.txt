cmake_minimum_required(VERSION 3.5)
project(legoHouse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(legoHouse main.cpp)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(legoHouse ${OpenCV_LIBS})
