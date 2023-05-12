#include "catch.hpp"
#include "texture/ktxcontainer/ktxcontainer.h"
#include "texture/ktxcontainer/ktxexception.h"

#include <filesystem>
#include <string>

#define CONFIG_CATCH_MAIN

TEST_CASE("Load container fails with invalid file", "[ktxtexturecontainer]")
{
    std::string const WRONG_FILE = "wrongfile";
    REQUIRE_THROWS_AS(KTXTextureContainer{WRONG_FILE}, std::filesystem::filesystem_error);
}

TEST_CASE("Loading OpenGL Texture throws exception when texture mipmap level is invalid", "[ktxtexturecontainer]")
{
    GLuint texture;
    GLuint target;
    KTXTextureContainer container {KTX_EXCEPTION_FILE};
    REQUIRE_THROWS_AS(container.GenerateGLTexture(texture, target), KTXException);
}
