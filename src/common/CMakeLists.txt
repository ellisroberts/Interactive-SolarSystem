add_library(Debug INTERFACE)
target_include_directories(Debug INTERFACE .)
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    target_compile_definitions(Debug INTERFACE DEBUG_BUILD)
endif()
