#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <iostream>

struct DeleteWindow
{
	void operator()(GLFWwindow *pWindow)
	{
		glfwDestroyWindow(pWindow);
    }
};

//Invariants - m_window must be unique and not shared with other Window classes
//           -m_Window must point to valid window
//Universal PreCondition -Glfw must be initialized
class Window
{
public:
	explicit Window(GLuint Height, GLuint Width, std::string const& Name);
	void MakeContextCurrent();
	Window(Window &&Other) = default;
	Window& operator=(Window &&Other) = default;
	~Window() = default;
private:
	std::unique_ptr<GLFWwindow, DeleteWindow> m_pWindow;
};
