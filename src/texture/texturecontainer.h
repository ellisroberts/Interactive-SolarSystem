#include <GL/glew.h>
#include <string>

class TextureContainer
{
    public:
    //Generate an OpenGL texture object
    virtual GenerateGLTexture(GLuint &TextureOut,
                              GLuint &TargetOut);
    protected:
    TextureContainer& operator=(TextureContainer const& Other) = default;
    TextureContainer& operator=(TextureContainer&& Other) = default;
};
