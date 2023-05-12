#pragma once

#include <GL/glew.h>
#include <cassert>
#include <string>

class ShaderProgram;

class ShaderObject
//Invariants: If Handle non-zero, it is unique to this instance
//Moved-from-state : IsMoved should be true
{
public:
    //PreCondition: There must be an active opengl context
    ShaderObject(GLuint ShaderType);
    //Pre-Condition : Other must have valid handle
    ShaderObject(ShaderObject &&Other);
    ShaderObject& operator=(ShaderObject &&Other) = delete;
    ~ShaderObject();
    //Pre-Condition: IsAttached is false
    //PreCondition: There must be an active opengl context
    //Pre-Condition : Shader must have valid handle
    template <typename Code>
    void AttachSource(Code&& SourceCode)
    {
        static_assert(std::is_same<std::string, typename std::remove_reference<Code>::type>::value ||
                      std::is_same<std::string const, typename std::remove_reference<Code>::type>::value);
        assert(m_ShaderHandle && !m_IsAttached);
        m_SourceCode = std::forward<Code>(SourceCode);
        auto sourceCode = m_SourceCode.c_str();
        glShaderSource(m_ShaderHandle, 1, &sourceCode, NULL);
        m_IsAttached = true;
    }
    //Pre-Condtion: Compile Attempted is false and IsAttached is true
    //PreCondition: There must be an active opengl context
    //Pre-Condition : Shader must have valid handle
    void Compile();
    bool IsAttached() const {return m_IsAttached;}
    bool IsCompiled() const {return m_IsCompiled;}
    bool WasAttempted() const {return m_CompileAttempted;}
    GLuint GetShaderHandle() const {return m_ShaderHandle;}
    std::string GetSourceCode() const {return m_SourceCode;}
    GLuint GetShaderType() const {return m_ShaderType;}
    bool IsMoved() {return !m_ShaderHandle && ! m_IsAttached && !m_IsCompiled && !m_CompileAttempted;}
private:
    GLuint m_ShaderHandle = 0;
    GLuint m_ShaderType = GL_VERTEX_SHADER;
    bool m_IsAttached = false;
    GLint m_IsCompiled = GL_FALSE;
    bool m_CompileAttempted = false;
    std::string m_SourceCode = "";
};
