#include "glfwhelper/glfwhelper.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include <stdexcept>

int main( int argc, char* argv[] )
{
    int result;
    //initialize glfw
    try
    {
        GLFWHelper::GLFW::Initialize();
    }
    catch (std::runtime_error& e)
    {
        return -1;
    }
    {        
        // setup context
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        GLFWHelper::Window window(640, 480, std::string{"My Window"});
        window.MakeContextCurrent();
        
        // initialize glew
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            // Problem: glewInit failed, something is seriously wrong.
            std::cerr << "GLEW could not initialize" << std::endl;
        }
        result = Catch::Session().run(argc, argv);
    }

    return result;
}
