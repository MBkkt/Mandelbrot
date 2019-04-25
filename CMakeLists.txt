cmake_minimum_required(VERSION 3.13)

project(Mandelbrot)
set(EXECUTABLE_NAME "Mandelbrot")

set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -Wextra -Werror -Ofast -pthread")

include_directories(inc)

add_executable(${EXECUTABLE_NAME} src/main.cpp src/Mandelbrot.cpp)

find_package(SFML 2 REQUIRED network audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

