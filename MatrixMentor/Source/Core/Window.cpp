#include "mmpch.h"

#include "Core/Window.h"

bool Window::Create(const WindowSpecification& spec, Window* outWindow)
{
	if (!glfwInit())
	{
		const char* error;
		glfwGetError(&error);
		MM_ERROR("Failed to initialise GLFW! Error: {0}", error);
		return false;
	}
	else
	{
		const char* version = glfwGetVersionString();
		MM_INFO("Successfully initialised GLFW ({0})", version);
	}

	GLFWwindow* window = nullptr;
	glfwWindowHint(GLFW_VISIBLE, false);
	glfwWindowHint(GLFW_RESIZABLE, spec.Resizeable);
	window = glfwCreateWindow(spec.Width, spec.Height, spec.Title.c_str(), nullptr, nullptr);

	if (!window)
	{
		const char* error;
		glfwGetError(&error);
		MM_ERROR("Failed to create GLFW window! Error: {0}", error);
		glfwTerminate();
		return false;
	}

	if (spec.Centered)
	{
		int count;
		int monitorX, monitorY;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
		glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
		glfwSetWindowPos(window,
			monitorX + (videoMode->width - spec.Width) / 2,
			monitorY + (videoMode->height - spec.Height) / 2);
	}

	glfwShowWindow(window);

	// Initialise OpenGL context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(spec.VSync ? 1 : 0);

	outWindow = new Window(window);
	return true;
}

Window::Window(GLFWwindow* window)
	: m_Window(window)
{
}

Window::~Window()
{
	// For now, assume there's only one window, so terminate on destruction.
	if (m_Window)
		glfwDestroyWindow(m_Window);
	glfwTerminate();
}
