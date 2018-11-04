cmake_minimum_required(VERSION 3.12)
project(project_delta)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cmake-build-debug)

add_executable(project_delta
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/project_delta
        cmake-build-debug/project_delta.cbp
        CMakeLists.txt
        data.csv
        main.cpp
        project-delta.zip)
