#include "glfwhelper/glfwhelper.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
    //initialize glfw
    try
    {
        GLFWHelper::GLFW::Initialize();
    }
    catch (std::runtime_error& e)
    {
        return -1;
    }
    
    //Make opengl context
    GLFWHelper::Window window(640, 480, std::string{"My Window"});
    window.MakeContextCurrent();

    // initialize glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        std::cerr << "GLEW initialization failed with code" << err << std::endl;
        return -1;
    }
    
    //Load in the scene
    Assimp::Importer importer;
    auto scene = importer.ReadFile("models/sun.blend", 0);
    if (!scene)
    {
        std::cerr << "Couldn't Load the scene file" << std::endl;
        return -1;
    }
    
    //Generate the shaders
    
    //Generate the vertex array objects
    
    //Generate the textures and set sampling
    
    //Draw loop
    
     return err;
}
