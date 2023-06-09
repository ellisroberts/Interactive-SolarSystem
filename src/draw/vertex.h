#pragma once
#include "buffer.h"

#include <GL/glew.h>
#include <tuple>
#include <vector>

using BindTuple = std::tuple<GLuint, GLuint, GLenum, GLboolean, GLuint, GLuint64>;

namespace GLObject
{
    struct BindParams
    {
        GLuint index;
        GLuint size;
        GLenum type;
        GLboolean isNormalized;
        GLuint stride;
        GLuint64 offset;
    };
    
    bool operator ==(BindParams const& First, BindParams const& Second);
    
    //Invariant: VAO handle must refer to a valid VAO object and all buffers must be bound to attribute
    class VAO
    {
    public:
        VAO()
        {
            glGenVertexArrays(1, &m_Handle);
            assert(m_Handle);
        }
        VAO(VAO const& Other) = delete;
        VAO& operator=(VAO const& Other) = delete;
        VAO(VAO && Other) = delete;
        VAO& operator=(VAO&& Other) = delete;
        ~VAO()
        {
            glDeleteVertexArrays(1, &m_Handle);
        }

        //Get Handle of vertex array to pass to gl functions
        auto GetHandle() {return m_Handle;}
        //Bind buffer and add to VAO
        void AddVertexBuffer(Buffer&& VertexBuffer, std::vector<BindParams> const& Params);
    private:
        GLuint m_Handle;
        std::vector<Buffer> m_Buffers;
    };
}
