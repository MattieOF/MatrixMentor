#include "mmpch.h"

#include "Core/Window.h"

#include <GLFW/glfw3.h>

bool Window::Create(const WindowSpecification& spec, Window*& outWindow)
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
		MM_INFO("Successfully initialised GLFW ({0})\n", version);
	}

	GLFWwindow* window = nullptr;
	glfwWindowHint(GLFW_VISIBLE, false);
	glfwWindowHint(GLFW_RESIZABLE, spec.Resizeable);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, spec.GLSettings.Major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, spec.GLSettings.Minor);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, spec.GLSettings.Core);
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
	
	MM_INFO("Successfully initialised window and OpenGL {0}.{1}{2}",
		spec.GLSettings.Major, spec.GLSettings.Minor, spec.GLSettings.Core ? " (Core)" : "");

	// Basic GL Setup
	glViewport(0, 0, spec.Width, spec.Height);
	const char* glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	MM_INFO("	Version: {0}", glVersion);
	MM_INFO("	GPU:     {0}", renderer);
	MM_INFO("	Vendor:  {0}", vendor);

	outWindow = new Window(window);
	return true;
}

void Window::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwSwapBuffers(m_Window);

		glfwPollEvents();
	}
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
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
