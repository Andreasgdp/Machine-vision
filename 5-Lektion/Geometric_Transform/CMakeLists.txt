cmake_minimum_required(VERSION 3.5)

project(Geometric_Transform LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Geometric_Transform main.cpp)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Geometric_Transform ${OpenCV_LIBS})
