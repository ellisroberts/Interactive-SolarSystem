#pragma once

#include "shaderobject.h"

#include <cassert>
#include <GL/glew.h>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

//Invariants : if shader handle is non zero, it is unique to this instance
// Moved-From-State : IsMoved must return true
class ShaderProgram
{
public:
    //PreCondition: There must be an active opengl context
    ShaderProgram();
    //Pre-Condition : Other must have valid handle
    ShaderProgram(ShaderProgram &&Other);
    ShaderProgram& operator=(ShaderProgram &&Other) = delete;
    ~ShaderProgram();
    //Pre-Condition: ShaderProgram is not linked and link has not been attempted
    //             : Shader must be successfully compiled
    //Pre-Condition : Program must have valid handle
    void AddShader(ShaderObject &&Shader);
    //Pre-Conditions: Program must not be linked and link has not been attempted
    //PreCondition: There must be an active opengl context
    //Pre-Condition : Program must have valid handle
    void LinkShader();
    GLint IsLinked() const {return m_IsLinked;}
    bool IsLinkAttempted() const {return m_LinkAttempted;}
    GLuint GetProgramHandle() const {return m_ProgramHandle;}
    bool IsMoved() {return !m_ProgramHandle && !m_IsLinked && !m_LinkAttempted && m_AttachedShaderHandles.empty();}
    

private:
    //Pre-Condition: Shader Object Must be compiled
    // and Shader Program is not linked
    //PreCondition: There must be an active opengl context
    //Pre-Condition : Program must have valid handle
    void AttachShader(ShaderObject &Object);
    //Pre-Condition: Shader Object must be compiled
    // and Shader Program is Linked
    //PreCondition: There must be an active opengl context
    //Pre-Condition : Program must have valid handle
    void DetachShader(ShaderObject &Object);

    GLuint m_ProgramHandle = 0;
    GLint m_IsLinked = GL_FALSE;
    bool m_LinkAttempted = false;
    std::vector<ShaderObject> m_AttachedShaderHandles = {};
};
