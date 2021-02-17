# CMakeList.txt : CMake project for template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Hivemind")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory ("ImplantFramework")
add_subdirectory ("docs")
