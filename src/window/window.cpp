#include "window.h"
#include "debug.h"

#include <assert.h>

Window::Window(GLuint Height, GLuint Width, std::string const& Name)
{
    m_pWindow = std::unique_ptr<GLFWwindow, DeleteWindow>(glfwCreateWindow(Height, Width, Name.c_str(), nullptr, nullptr));
    Debug::DebugPrint("GLFW Error is ", glfwGetError(nullptr));
    assert(m_pWindow);
}

void Window::MakeContextCurrent()
{
    assert(m_pWindow);
    glfwMakeContextCurrent(m_pWindow.get());
    Debug::DebugPrint("GLFW Error is ", glfwGetError(nullptr));
}
