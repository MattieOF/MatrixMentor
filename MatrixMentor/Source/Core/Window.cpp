#include "mmpch.h"

#include "Core/Window.h"

#include <GLFW/glfw3.h>

#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Input/Input.h"

static void GLFWErrorCallback(int error, const char* desc)
{
	MM_ERROR("GLFW Error ({0}): {1}", error, desc);
}

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
		glfwSetErrorCallback(GLFWErrorCallback);
	}

	GLFWwindow* window = nullptr;
	glfwWindowHint(GLFW_VISIBLE, false);
	glfwWindowHint(GLFW_RESIZABLE, spec.Resizeable);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, spec.GLSettings.Major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, spec.GLSettings.Minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, spec.GLSettings.Core ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
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

	// Init input
	delete Input::s_Instance;
	Input::s_Instance = new GlfwInput();
	reinterpret_cast<GlfwInput*>(Input::s_Instance)->Window = window;

	// Setup GLFW event callbacks
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
		// Get data struct from the window
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		// Update data structs width and height values
		data.Width = width;
		data.Height = height;

		// Create a resize event and dispatch it
		WindowResizeEvent e(width, height);
		data.EventCallback(e);
	});

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
	{
		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		WindowCloseEvent e;
		data.EventCallback(e);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressedEvent e(key, false);
				data.EventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent e(key);
				data.EventCallback(e);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent e(key, true);
				data.EventCallback(e);
				break;
			}
			default: break;
		}
	});

	glfwSetCharCallback(window, [](GLFWwindow* window, unsigned codepoint)
	{
		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		KeyTypedEvent e(codepoint);
		data.EventCallback(e);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
	{
		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent e(button);
				data.EventCallback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent e(button);
				data.EventCallback(e);
				break;
			}
			default: break;
		}
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
	{
		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		MouseScrolledEvent e(xoffset, yoffset);
		data.EventCallback(e);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
	{
		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		MouseMovedEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
		data.EventCallback(e);
	});

	outWindow = new Window(spec, window);
	return true;
}

void Window::Run()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();

		for (Layer* layer : m_Layers)
			layer->OnUpdate(0);

		glClearColor(0.1f, 0.2f, 0.7f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_Window);
	}
}

void Window::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	
	// Propagate the event to all layers, starting with the topmost layer/overlay, down to the base layer. 
	for (auto it = m_Layers.end(); it != m_Layers.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.Handled)
			break;
	}
}

void Window::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerStackInsert, layer);
	m_LayerStackInsert++;
	layer->OnAttach();
}

void Window::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
	overlay->OnAttach();
}

void Window::PopLayer(Layer* layer)
{
	const auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	if (it != m_Layers.end())
	{
		layer->OnDetach();
		m_Layers.erase(it);
		m_LayerStackInsert--;
	}
}

void Window::PopOverlay(Layer* overlay)
{
	const auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end())
	{
		overlay->OnDetach();
		m_Layers.erase(it);
	}
}

void Window::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_WindowData.VSync = enabled;
}

bool Window::IsVSync() const
{
	return m_WindowData.VSync;
}

void Window::SetClipboardText(const char* text) const
{
	glfwSetClipboardString(m_Window, text);
}

const char* Window::GetClipboardText() const
{
	return glfwGetClipboardString(m_Window);
}

void Window::SetWindowTitle(std::string_view newTitle)
{
	glfwSetWindowTitle(m_Window, newTitle.data());
	m_WindowData.Title = std::string(newTitle);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

Window::Window(const WindowSpecification& spec, GLFWwindow* window)
	: m_Window(window)
{
	m_WindowData.Title = spec.Title;
	m_WindowData.Width = spec.Width;
	m_WindowData.Height = spec.Height;
	m_WindowData.VSync = spec.VSync;
	m_WindowData.EventCallback = BIND_EVENT_FN(Window::OnEvent);
	glfwSetWindowUserPointer(m_Window, &m_WindowData);
}

Window::~Window()
{
	// Destroy layers
	for (Layer* layer : m_Layers)
	{
		layer->OnDetach();
		delete layer;
	}

	// Delete input instance
	delete Input::s_Instance;

	// For now, assume there's only one window, so terminate on destruction.
	if (m_Window)
		glfwDestroyWindow(m_Window);
	glfwTerminate();
}
