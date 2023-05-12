#pragma once

#include <GL/glew.h>
#include <string>

class TextureContainer
{
    public:
    //Generate an OpenGL texture object
    virtual void GenerateGLTexture(GLuint &TextureOut,
                                   GLuint &TargetOut) const = 0;
    ~TextureContainer() = default;
    protected:
    TextureContainer() = default;
    TextureContainer& operator=(TextureContainer const& Other) = default;
    TextureContainer& operator=(TextureContainer&& Other) = default;
};
