#include "gltexture.h"

#include <stdexcept>

GLTexture::GLTexture()
{
    glGenTextures(1, &m_Texture);
    if (!m_Texture)
        throw std::runtime_error {"Could not generate texture name"};
}

GLTexture::GLTexture(GLTexture &&Other) : m_Target {Other.m_Target},
                                          m_Loaded {Other.m_Loaded}
{
    std::swap(m_Texture, Other.m_Texture);
    Other.m_Loaded = GL_FALSE;
    assert(Other.IsMoved());
}

void GLTexture::LoadParametersFromContainer(TextureContainer const& Container)
{
    assert(m_Texture & !m_Loaded);
    Container.GenerateGLTexture(m_Texture, m_Target);
    m_Loaded = true;
}
