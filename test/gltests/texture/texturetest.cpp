#include "catch.hpp"
#include "texture/ktxcontainer/ktxcontainer.h"
#include "texture/gltexture.h"

#define GET_TEX_PARAM(ParamName) [](GLenum Target) \
                                 { \
                                     GLint param; \
                                     glGetTexLevelParameteriv(Target, 0, GL_##ParamName, &param); \
                                     return param; \
                                 }
                                 
TEST_CASE("Generate a desired 2D OpenGL Texture from a KTX container", "[Texture]")
{
    GLuint TEXTURE_HEIGHT = 3000;
    GLuint TEXTURE_WIDTH = 3000;
    GLTexture texture;
    KTXTextureContainer container {CONTAINER_FILE_2D};
    texture.LoadParametersFromContainer(container);
    
    REQUIRE(texture.GetTarget() == GL_TEXTURE_2D);
    REQUIRE(GET_TEX_PARAM(TEXTURE_INTERNAL_FORMAT)(texture.GetTarget()) == GL_SRGB8);
    REQUIRE(GET_TEX_PARAM(TEXTURE_HEIGHT)(texture.GetTarget()) == TEXTURE_HEIGHT);
    REQUIRE(GET_TEX_PARAM(TEXTURE_WIDTH)(texture.GetTarget()) == TEXTURE_WIDTH);
}
