add_library(shader OBJECT shaderobject.cpp shaderprogram.cpp)

target_link_libraries(shader PUBLIC GLEW::GLEW) 
