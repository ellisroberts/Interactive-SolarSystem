#include "shaderobject.h"

#include <iostream>
#include <stdexcept>

ShaderObject::ShaderObject(GLuint ShaderType) : m_ShaderType {ShaderType}
{
    m_ShaderHandle = glCreateShader(m_ShaderType);
    if (!m_ShaderHandle)
        throw std::runtime_error {"Could not create shader handle"};
}

ShaderObject::ShaderObject(ShaderObject &&Other) :
    m_ShaderHandle {Other.m_ShaderHandle},
    m_ShaderType {Other.m_ShaderType},
    m_IsAttached {Other.m_IsAttached},
    m_IsCompiled {Other.m_IsCompiled},
    m_CompileAttempted {Other.m_CompileAttempted},
    m_SourceCode {std::move(Other.m_SourceCode)}
{
    Other.m_ShaderHandle = 0;
    Other.m_IsAttached = false;
    Other.m_IsCompiled = GL_FALSE;
    Other.m_CompileAttempted = false;
    assert(Other.IsMoved());
}

ShaderObject::~ShaderObject()
{
    if (m_ShaderHandle)
        glDeleteShader(m_ShaderHandle);
}

void ShaderObject::Compile()
{
    assert(m_ShaderHandle && !m_CompileAttempted && m_IsAttached);

    glCompileShader(m_ShaderHandle);

    glGetShaderiv(m_ShaderHandle, GL_COMPILE_STATUS, &m_IsCompiled);
    if(m_IsCompiled == GL_FALSE)
    {
    	GLint maxLength = 0;
    	glGetShaderiv(m_ShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

    	// The maxLength includes the NULL character
    	std::string infoLog (maxLength, ' ');
    	glGetShaderInfoLog(m_ShaderHandle, maxLength, &maxLength, &infoLog[0]);
    	std::cerr << infoLog << std::endl;
    }
    m_CompileAttempted = true;
}
