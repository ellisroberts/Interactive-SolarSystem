#include "glhelperfunctions.h"

#include <fstream>
#include <iostream>
#include <iterator>

std::string GLHelper::GetSourceCode(path const& Path)
{
    auto filePath = Path.string();
    std::ifstream ifs{filePath};
    if (!ifs)
    {
        throw std::filesystem::filesystem_error {filePath + " Not Found", std::error_code{}};
    }
    ifs.unsetf(std::ios_base::skipws);
    std::istream_iterator<char> begin{ifs};
    std::istream_iterator<char> end{};
    return std::string{begin, end};
}

ShaderObject GLHelper::MakeShaderObject(GLuint ShaderType, std::string const& SourceCode)
{
	ShaderObject shader {ShaderType};
	shader.AttachSource(SourceCode);
	shader.Compile();
	return shader;
}

ShaderProgram GLHelper::MakeShaderProgram(std::vector<ShaderObject>& ShaderObjects)
{
	ShaderProgram program {};
	for (auto& object : ShaderObjects)
	{
		program.AddShader(std::move(object));
	}
	program.LinkShader();
	return program;
}
