add_library(GLObject OBJECT vertex.cpp)

target_include_directories(GLObject INTERFACE .)
target_link_libraries(GLObject
                      PUBLIC GLEW::GLEW
                      PUBLIC Debug)
