#pragma once

#ifdef DEBUG_BUILD
#include <exception>
#include <GL/glew.h>
#include <iostream>
#include <string>
namespace Debug
{
    template <typename... Types>
    inline void DebugPrint(Types&& ...Args)
    {
        (std::cout << ... << std::forward<Types> (Args)) << std::endl;
    }

    inline void CheckGLError()
    {
        auto error = glGetError();
        if (error != GL_NO_ERROR)
        {
            throw std::runtime_error {"OpenGL call failed"};
        }
    }
}
#else
namespace Debug
{
    template <typename... Types>
    inline void DebugPrint(Types&& ...Args)
    {
        ((void) 0);
    }

    inline void CheckGLError()
    {
        ((void) 0);
    }
}
#endif 
