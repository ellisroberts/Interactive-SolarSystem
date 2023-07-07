add_executable(main main.cpp)

target_link_libraries(main PRIVATE assimp::assimp)
target_link_libraries(main PRIVATE glfwhelper)
