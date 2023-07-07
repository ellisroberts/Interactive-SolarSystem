#include "glfwhelper.h"
#include "debug.h"

#include <cassert>
#include <stdexcept>

GLFWHelper::Window::Window(GLuint Height, GLuint Width, std::string const& Name)
{
    m_pWindow = std::unique_ptr<GLFWwindow, DeleteWindow>(glfwCreateWindow(Height, Width, Name.c_str(), nullptr, nullptr));
    Debug::DebugPrint("GLFW Error is ", glfwGetError(nullptr));
    assert(m_pWindow);
}

void GLFWHelper::Window::MakeContextCurrent()
{
    assert(m_pWindow);
    glfwMakeContextCurrent(m_pWindow.get());
    Debug::DebugPrint("GLFW Error is ", glfwGetError(nullptr));
}


std::unique_ptr<GLFWHelper::GLFW> GLFWHelper::GLFW::m_GLFW = nullptr;

GLFWHelper::GLFW::GLFW()
{
    auto result = glfwInit();
    if (!result)
        throw std::runtime_error {"GLFW could not be initialized"};;
}
