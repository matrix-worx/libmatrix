cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(libmatrix CXX C)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(library_sources
    CMatrix.hpp
    CMatrix.cpp
    CMatrixException.hpp
    CMatrixException.cpp
    MatrixIO.hpp
    MatrixIO.cpp
)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost
    REQUIRED
    COMPONENTS system thread
)

add_subdirectory(gsl ${CMAKE_BINARY_DIR}/gsl/ EXCLUDE_FROM_ALL)
include_directories(gsl
                    ${CMAKE_BINARY_DIR}/gsl/)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${Boost_INCLUDE_DIRS})

include(GenerateExportHeader)

add_library(matrix STATIC ${library_sources})
target_link_libraries(matrix gsl ${Boost_LIBRARIES})
generate_export_header(matrix)
add_compiler_export_flags()
