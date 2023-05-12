#include "shaderprogram.h"

#include <algorithm>
#include <type_traits>
#include <regex>
#include <stdexcept>

ShaderProgram::ShaderProgram()
{
    m_ProgramHandle = glCreateProgram();
    if (!m_ProgramHandle)
        throw std::runtime_error {"Could not create shader program handle"};
}

ShaderProgram::ShaderProgram(ShaderProgram &&Other) :
    m_ProgramHandle {Other.m_ProgramHandle},
    m_IsLinked {Other.m_IsLinked},
    m_LinkAttempted {Other.m_LinkAttempted},
    m_AttachedShaderHandles {std::move(Other.m_AttachedShaderHandles)}
{
    Other.m_ProgramHandle = 0;
    Other.m_IsLinked = GL_FALSE;
    Other.m_LinkAttempted = false;
    assert(Other.IsMoved());
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ProgramHandle);
}

void ShaderProgram::AddShader(ShaderObject &&Shader)
{
    assert(m_ProgramHandle && Shader.IsCompiled() && !m_IsLinked && !m_LinkAttempted);
    m_AttachedShaderHandles.push_back(std::move(Shader));
}

void ShaderProgram::AttachShader(ShaderObject &Object)
{
    assert(m_ProgramHandle && Object.IsCompiled() && !m_IsLinked && !m_LinkAttempted);
    glAttachShader(m_ProgramHandle, Object.GetShaderHandle());
}

void ShaderProgram::DetachShader(ShaderObject &Object)
{
    assert(m_ProgramHandle && Object.IsCompiled() && m_LinkAttempted);
    glDetachShader(m_ProgramHandle, Object.GetShaderHandle());
}

void ShaderProgram::LinkShader()
{
    assert(m_ProgramHandle && !m_IsLinked && !m_LinkAttempted);
    // Attach our shaders to our program
    for (auto &handle : m_AttachedShaderHandles)
    {
        AttachShader(handle);
    }

    // Link our program
    glLinkProgram(m_ProgramHandle);

    glGetProgramiv(m_ProgramHandle, GL_LINK_STATUS, &m_IsLinked);
    if (m_IsLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_ProgramHandle, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::string infoLog(maxLength, ' ');
        glGetProgramInfoLog(m_ProgramHandle, maxLength, &maxLength, &infoLog[0]);

        std::cerr << infoLog << std::endl;
    }
    
    m_LinkAttempted = true;

    // Always detach shaders after a successful or unsuccessful link
    for (auto &handle : m_AttachedShaderHandles)
    {
        DetachShader(handle);
    }
}
