#include "catch.hpp"
#include "vertex.h"

#include <iostream>

namespace
{
    //Extract attribute parameters back into struct
    GLObject::BindParams GetBindParamsFromAttribute(GLuint Index)
    {
        GLuint isNormalized;
        void *offset = nullptr;
        GLObject::BindParams params;
        
        params.index = Index;
        glGetVertexAttribIuiv(Index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &params.size);
        glGetVertexAttribIuiv(Index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &params.type);
        glGetVertexAttribIuiv(Index, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &isNormalized);
        params.isNormalized = isNormalized ? true : false;
        glGetVertexAttribIuiv(Index, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &params.stride);
        glGetVertexAttribPointerv(Index, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);
        params.offset = reinterpret_cast<GLuint64> (offset);
        return params;
    }
}

TEST_CASE("Ensure Buffer Object is created as expected", "[Buffer]")
{
    std::vector<GLuint> input{0, 1, 2, 3};
    auto vectorBuffer = GLObject::CreateBufferObject(input, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    GLuint output[4];
    glGetNamedBufferSubData(vectorBuffer.GetHandle(), 0, input.size()*sizeof(GLuint), output);
    REQUIRE(std::equal(input.begin(), input.end(), output));
}

TEST_CASE("Ensure the VAO is initialized with attributes enabled", "[VAO]")
{
    GLObject::VAO vao;
    std::vector<GLuint> input{0, 1, 2, 3};
    GLObject::BindParams params1 {0, 2, GL_UNSIGNED_INT, true, 2, 0};
    GLObject::BindParams params2 {1, 2, GL_UNSIGNED_INT, true, 2, 2};
    vao.BindBuffer(GLObject::CreateBufferObject(input, GL_ARRAY_BUFFER, GL_STATIC_DRAW), {params1, params2});
    
    glBindVertexArray(vao.GetHandle());
    REQUIRE(GetBindParamsFromAttribute(0) == params1);
    REQUIRE(GetBindParamsFromAttribute(1) == params2);
}
