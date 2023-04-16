cmake_minimum_required(VERSION 3.22...3.25)
project(SolarSystem LANGUAGES CXX)

#Set CMAKE variables and include_directories for project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#include project-wide directories
include_directories(AFTER src)

#CACHE variables
option(Debug_Mode "DebugMode" ON)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

#include external packages
include(external/findpackages.cmake)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()
