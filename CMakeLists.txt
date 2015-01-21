cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(libmatrix CXX C)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(library_sources
    CMatrix.hpp
    CMatrix.cpp
)

add_subdirectory(gsl ${CMAKE_BINARY_DIR}/gsl/ EXCLUDE_FROM_ALL)
include_directories(gsl
                    ${CMAKE_BINARY_DIR}/gsl/)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(matrix STATIC ${library_sources})
target_link_libraries(matrix gsl)
