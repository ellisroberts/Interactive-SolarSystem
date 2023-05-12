#pragma once

#include "texturecontainer.h"

#include <cassert>
#include <cstdint>
#include <GL/glew.h>
#include <string>
#include <vector>

//Invariants : If texture handle is valid (non-zero), it should be unique to owning object
//Universal pre-condition : texture handle must be valid (non-zero)
//Moved from state : IsMoved should be true
class GLTexture
{
public:
    GLTexture();
    GLTexture(GLTexture &&Other);
    GLTexture& operator=(GLTexture &&Other) = delete;
    
    //Load the texture from texture container file
    void LoadParametersFromContainer(TextureContainer const& Container);
    
    //Pre-Condition : Texture has been loaded from container
    GLenum GetTarget() const
    {
        assert(m_Loaded & m_Texture);
        return m_Target;
    }
    
    GLuint GetHandle() const
    {
        assert(m_Texture);
        return m_Texture;
    }
    
    bool IsMoved() const {return !m_Texture && !m_Loaded;}

private:
    GLuint m_Texture = 0;
    GLenum m_Target = GL_TEXTURE_1D;
    bool m_Loaded = false;
};
