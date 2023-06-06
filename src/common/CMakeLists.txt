add_library(Debug INTERFACE)
if ("${CMAKE_BUILD_TYPE}" EQUAL "Debug")
    target_compile_definitions(Debug INTERFACE DEBUG_BUILD)
endif()
