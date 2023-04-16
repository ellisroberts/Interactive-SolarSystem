#pragma once

#include "../shader/shaderprogram.h"
#include "../shader/shaderobject.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

using path = std::filesystem::path;

namespace GLHelper
{
     std::string GetSourceCode(path const& Path);
     //Pre-Conditions, opengl context must be current on calling thread
     ShaderObject MakeShaderObject(GLuint ShaderType, std::string const& SourceCode);
     //Pre-Conditions, opengl context must be current on calling thread
     ShaderProgram MakeShaderProgram(std::vector<ShaderObject>& ShaderObjects);
}
