#include "glhelperfunctions/glhelperfunctions.h"
#include "shader/shaderobject.h"

#include <catch2/catch.hpp>
#include <glm/glm.hpp>
#include <exception>
#include <filesystem>
#include <utility>

#define BUILD_SHADER(type, code) GLHelper::MakeShaderObject(type, code)
#define GET_CODE(path) GLHelper::GetSourceCode(path)

TEST_CASE("Shader Object compiles properly provided shader code is correct", "[ShaderObject]")
{
    auto shaderPath = std::filesystem::current_path();

    SECTION("Shader compilation fails with incorrect shader code")
    {
        auto shader = BUILD_SHADER(GL_VERTEX_SHADER, GET_CODE(shaderPath /= path(WRONG_VERT_SHADER)));
        REQUIRE(!shader.IsCompiled());
        REQUIRE(shader.WasAttempted());
    }

    SECTION("Shader compilation succeeds with correct code")
    {
        auto shader = BUILD_SHADER(GL_VERTEX_SHADER, GET_CODE(shaderPath /= path(CORRECT_VERT_SHADER)));
        REQUIRE(shader.IsCompiled());
        REQUIRE(shader.WasAttempted());
    }
}
