#include "texture/ktx2container.h"

#include <catch2.hpp>
#include <filesystem>

TEST_CASE("Load container fails with invalid file", "[ktx2container]")
{
    REQUIRE_THROWS_AS(Ktx2Container container {"wrongFile"}, std::filesystem::filesystem_error);
}

TEST_CASE("Loading OpenGL Texture throws exception when texture mipmap level is invalid", "[ktx2container]")
{
    GLuint texture;
    GLuint target;
    Ktx2Container container {KTX2_EXCEPTION_FILE};
    REQUIRE_THROWS_AS(container.GenerateGLTexture(texture, target), KTX2Exception);
}
