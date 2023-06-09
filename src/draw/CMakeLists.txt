add_library(GLObject INTERFACE)

target_include_directories(GLObject INTERFACE .)
target_link_libraries(GLObject
                      INTERFACE GLEW::GLEW
                      INTERFACE Debug)
