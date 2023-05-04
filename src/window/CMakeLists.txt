add_library(window OBJECT window.cpp)

target_link_libraries(window INTERFACE Debug)
target_link_libraries(window PUBLIC GLEW::GLEW)
target_link_libraries(window PUBLIC glfw)
