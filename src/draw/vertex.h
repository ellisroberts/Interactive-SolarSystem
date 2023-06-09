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
    
    bool operator ==(BindParams const& First, BindParams const& Second)
    {
        return BindTuple{First.index, First.size, First.type, First.isNormalized, First.stride, First.offset} ==
               BindTuple{Second.index, Second.size, Second.type, Second.isNormalized, Second.stride, Second.offset};
    }
    
    //Invariant: VAO handle must refer to a valid VAO object and all bound buffers must be valid
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
        //Bind the buffer to an attribute
        void BindBuffer(Buffer&& VertexBuffer, std::vector<BindParams> const& Params)
        {
            //Bind to attributes
            glBindVertexArray(m_Handle);
            Debug::CheckGLError();
            glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer.GetHandle());
            Debug::CheckGLError();
            for (auto const& param : Params)
            {
                glEnableVertexAttribArray(param.index);
                Debug::CheckGLError();
                glVertexAttribPointer(param.index, param.size, param.type,
                                      param.isNormalized, param.stride,
                                      reinterpret_cast<void *> (param.offset));
                Debug::CheckGLError();
            }
            //UnBind
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            //Store Buffer to ensure it lives for lifetime of VAO object
            m_Buffers.push_back(std::move(VertexBuffer));     
        }
    private:
        GLuint m_Handle;
        std::vector<Buffer> m_Buffers;
    };
}
