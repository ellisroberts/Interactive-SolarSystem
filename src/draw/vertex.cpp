#include "vertex.h"

namespace
{
    void BindBufferToVertexAttribute(GLObject::Buffer&& VertexBuffer, std::vector<GLObject::BindParams> const& Params)
    {
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
    }
}

void GLObject::VAO::AddVertexBuffer(Buffer&& VertexBuffer, std::vector<BindParams> const& Params)
{
    //Bind to attributes
    glBindVertexArray(m_Handle);
    Debug::CheckGLError();
    BindBufferToVertexAttribute(std::move(VertexBuffer), Params);
    glBindVertexArray(0);
    //Store Buffer to ensure it lives for lifetime of VAO object
    m_Buffers.push_back(std::move(VertexBuffer));    
}

bool GLObject::operator ==(BindParams const& First, BindParams const& Second)
{
    return BindTuple{First.index, First.size, First.type, First.isNormalized, First.stride, First.offset} ==
           BindTuple{Second.index, Second.size, Second.type, Second.isNormalized, Second.stride, Second.offset};
}
