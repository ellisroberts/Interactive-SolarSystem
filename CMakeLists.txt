cmake_minimum_required(VERSION 3.22...3.25)

#vcpkg configuration
#set(VCPKG_TARGET_TRIPLET "" CACHE STRING "")
#set(VCPKG_HOST_TRIPLET "" CACHE STRING "")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")
    
project(SolarSystem LANGUAGES CXX)

#Set CMAKE variables and include_directories for project
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#include project-wide directories
include_directories(AFTER src)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

#include external packages
include(external/findpackages.cmake)

add_subdirectory(src)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()
