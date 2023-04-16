#include "window/window.h"

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>
#include <iostream>

int main( int argc, char* argv[] )
{
    //initialize glfw
    int result = glfwInit();
    if (!result)
        goto end;

    {        
        // setup context
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        Window window(640, 480, "My Window");
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

end:
    glfwTerminate();
    return result;
}
