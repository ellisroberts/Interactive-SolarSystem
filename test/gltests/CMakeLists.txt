add_library(glmain STATIC glmain.cpp)

target_link_libraries(glmain PRIVATE glfwhelper)
target_link_libraries(glmain PRIVATE Catch2::Catch2)

add_subdirectory(shader)
add_subdirectory(texture)
add_subdirectory(draw)
