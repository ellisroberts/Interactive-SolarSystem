#include "texture/ktx2container.h"
#include "texture/texture.h"

#include <catch2.hpp>

TEST_CASE("Generate a desired 2D OpenGL Texture from a KTX2 container", [Texture])
{
    GLTexture texture;
    Ktx2Container container {2D_CONTAINER_FILE};
    texture.LoadParametersFromContainer(container);
    REQUIRE(texture.GetTarget() == GL_TEXTURE_2D);
    REQUIRE(texture.GetParameter(GL_TEXTURE_INTERNAL_FORMAT) == DESIRED_FORMAT);
    REQUIRE(texture.GetParameter(GL_TEXTURE_WIDTH) == DESIRED_WIDTH);
    REQUIRE(texture.GetParameter(GL_TEXTURE_HEIGHT) == DESIRED_HEIGHT);
}
