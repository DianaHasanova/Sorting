cmake_minimum_required(VERSION 3.20)
project(labSorting C)

set(CMAKE_C_STANDARD 11)

add_executable(labSorting main.c libs/sortingAlgorithms/sortingAlgorithms.c libs/sortingAlgorithms/sortingAlgorithms.h)

add_subdirectory(libs)