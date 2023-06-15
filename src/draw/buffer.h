#pragma once
#include "debug.h"

#include <algorithm>
#include <cassert>
#include <GL/glew.h>
#include <type_traits>
#include <vector>

//Moved from state: buffer handle is 0
namespace GLObject
{
    class Buffer
    {
    public:
        Buffer()
        {
            glGenBuffers(1, &m_Handle);
        }
        Buffer(Buffer const& Other) = delete;
        Buffer& operator=(Buffer const& Other) = delete;
        Buffer(Buffer && Other) : m_Handle {Other.m_Handle}
        {
            Other.m_Handle = 0;
        }
        Buffer& operator=(Buffer && Other)
        {
            std::swap(m_Handle, Other.m_Handle);
            return *this;
        }
        
        ~Buffer()
        {
            glDeleteBuffers(1, &m_Handle);
        }
        
        //Pre-condition: buffer must not be moved from
        auto GetHandle() 
        {
            assert(m_Handle);
            return m_Handle;
        }
    private:
        GLuint m_Handle;
    };
    
    template <typename T>
    //Create a buffer from input data to be bound to desired target
    Buffer CreateBufferObject(std::vector<T> const& Data, GLenum Target, GLenum Usage)
    {
        static_assert(std::is_arithmetic_v<T>);
        Buffer buffer;
        glBindBuffer(Target, buffer.GetHandle());
        Debug::CheckGLError();
        glBufferData(Target, Data.size()*sizeof(T), Data.data(), Usage);
        Debug::CheckGLError();
        glBindBuffer(Target, 0);
        return buffer;
    }
}
