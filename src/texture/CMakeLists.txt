add_subdirectory(ktxcontainer)

add_library(gltexture OBJECT gltexture.cpp)

target_link_libraries(gltexture PUBLIC GLEW::GLEW)
