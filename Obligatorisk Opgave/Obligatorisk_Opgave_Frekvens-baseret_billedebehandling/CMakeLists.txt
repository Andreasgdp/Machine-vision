cmake_minimum_required(VERSION 3.5)

project(Obligatorisk_Opgave_Frekvens-baseret_billedebehandling LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Obligatorisk_Opgave_Frekvens-baseret_billedebehandling main.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Obligatorisk_Opgave_Frekvens-baseret_billedebehandling  ${OpenCV_LIBS})
