add_library(glfwhelper OBJECT glfwhelper.cpp)

target_link_libraries(glfwhelper
                      PRIVATE Debug
                      PUBLIC GLEW::GLEW
                      PUBLIC glfw)
