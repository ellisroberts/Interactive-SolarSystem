#include "glhelperfunctions/glhelperfunctions.h"
#include "shader/shaderprogram.h"

#include "catch.hpp"
#include <glm/glm.hpp>
#include <exception>
#include <filesystem>
#include <utility>
#include <vector>

#define BUILD_SHADER(type, code) GLHelper::MakeShaderObject(type, code)
#define GET_CODE(path) GLHelper::GetSourceCode(path)

TEST_CASE("Linking fails with input with mismatching output/input", "[ShaderProgram]")
{
    std::vector<ShaderObject> basicShaders;
    auto shaderPath = std::filesystem::current_path();
 
    basicShaders.push_back(BUILD_SHADER(GL_VERTEX_SHADER, GET_CODE(shaderPath /= path(LINK_TEST_VERT_SHADER))));
    basicShaders.push_back(BUILD_SHADER(GL_FRAGMENT_SHADER, GET_CODE(shaderPath.replace_filename(LINK_TEST_FRAG_SHADER))));

    ShaderProgram program = GLHelper::MakeShaderProgram(basicShaders);
    REQUIRE(program.IsLinkAttempted());
    REQUIRE(!program.IsLinked());
}

TEST_CASE("Linking succeeds with correct shader input", "[ShaderProgram]")
{
    std::vector<ShaderObject> basicShaders;
    auto shaderPath = std::filesystem::current_path();
    
    basicShaders.push_back(BUILD_SHADER(GL_VERTEX_SHADER, GET_CODE(shaderPath /= path(CORRECT_VERT_SHADER))));
    basicShaders.push_back(BUILD_SHADER(GL_FRAGMENT_SHADER, GET_CODE(shaderPath.replace_filename(CORRECT_FRAG_SHADER))));

    ShaderProgram program = GLHelper::MakeShaderProgram(basicShaders);
    REQUIRE(program.IsLinkAttempted());
    REQUIRE(program.IsLinked());
}
