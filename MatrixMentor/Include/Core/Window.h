#pragma once
#include "GLFW/glfw3.h"

struct WindowSpecification
{
	std::string Title;
	int Width = 1280, Height = 600;
	bool VSync = false;
	bool Resizeable = true;
	bool Centered = true;
};

class Window
{
public:
	Window() = delete;
	~Window();

	static bool Create(const WindowSpecification& spec, Window* outWindow);

private:
	Window(GLFWwindow* window);

	GLFWwindow* m_Window = nullptr;
};
