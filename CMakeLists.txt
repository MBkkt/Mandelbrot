cmake_minimum_required(VERSION 3.13)

project(Mandelbrot)
set(EXECUTABLE_NAME "Mandelbrot")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -Werror -Ofast -pthread")

include_directories(inc)

add_executable(${EXECUTABLE_NAME} src/main.cpp src/Mandelbrot.cpp)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-system sfml-window)
