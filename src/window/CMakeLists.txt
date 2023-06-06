add_library(window OBJECT window.cpp)

target_link_libraries(window
                      PRIVATE Debug
                      PUBLIC GLEW::GLEW
                      PUBLIC glfw)
