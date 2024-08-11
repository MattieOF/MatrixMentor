#include "mmpch.h"

#include "Core/Window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h> // Include after glad!
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "imgui.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Input/Input.h"
#include "Core/Rendering/Renderer.h"

#ifndef MM_DONT_USE_DEDICATED
// This should force usage of a dedicated nvidia GPU over an integrated one, if multiple exist within a system.
// Thanks to http://stevendebock.blogspot.com/2013/07/nvidia-optimus.html and https://stackoverflow.com/a/39047129
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement                  = 1;
__declspec(dllexport) int           AmdPowerXpressRequestHighPerformance = 1;
}
#endif

ImFont* Window::s_NormalFont = nullptr;
ImFont* Window::s_BoldFont   = nullptr;

static void GLFWErrorCallback(int error, const char* desc)
{
	MM_ERROR("GLFW Error ({0}): {1}", error, desc);
}

static std::pair<int, int> GetGLADVersion(int version)
{
	std::pair<int, int> output;
	output.first = version / 10000;
	version -= output.first * 10000;
	output.second = version;
	return output;
}

void GLErrorCallback(GLenum      source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                     const void* userParam)
{
#ifndef MM_SHOW_GL_NOTIFICATIONS
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return;
#endif

#ifndef MM_NO_IGNORED_GL_ERROR_IDS
	static std::vector<GLuint> ignoredIDs = {131185};

	if (std::find(ignoredIDs.begin(), ignoredIDs.end(), id) != ignoredIDs.end())
		return;
#endif

	const char* sourceText;
	const char* typeText;
	const char* severityText;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		sourceText = "API";
		break;

	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourceText = "Window System";
		break;

	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourceText = "Shader Compiler";
		break;

	case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourceText = "Third Party";
		break;

	case GL_DEBUG_SOURCE_APPLICATION:
		sourceText = "Application";
		break;

	case GL_DEBUG_SOURCE_OTHER:
		sourceText = "Other";
		break;

	default:
		sourceText = "Unknown";
		break;
	}

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		typeText = "Error";
		break;

	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typeText = "Deprecated Behaviour";
		break;

	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typeText = "Undefined Behaviour";
		break;

	case GL_DEBUG_TYPE_PORTABILITY:
		typeText = "Portability";
		break;

	case GL_DEBUG_TYPE_PERFORMANCE:
		typeText = "Performance";
		break;

	case GL_DEBUG_TYPE_OTHER:
		typeText = "Other";
		break;

	case GL_DEBUG_TYPE_MARKER:
		typeText = "Marker";
		break;

	default:
		typeText = "Unknown";
		break;
	}

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		severityText = "High";
		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		severityText = "Medium";
		break;

	case GL_DEBUG_SEVERITY_LOW:
		severityText = "Low";
		break;

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severityText = "Notification";
		break;

	default:
		severityText = "Unknown";
		break;
	}

	MM_ERROR("OpenGL Error ({0} severity, id: {4}): from {1}, {2}: {3}", severityText, sourceText, typeText, message,
	         id);
	MM_ASSERT_ERROR(severity == GL_DEBUG_SEVERITY_NOTIFICATION);
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
	glfwDefaultWindowHints();
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
		int                count;
		int                monitorX, monitorY;
		GLFWmonitor**      monitors  = glfwGetMonitors(&count);
		const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
		glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);
		glfwSetWindowPos(window,
		                 monitorX + (videoMode->width - spec.Width) / 2,
		                 monitorY + (videoMode->height - spec.Height) / 2);
	}

	glfwShowWindow(window);

	MM_INFO("Successfully created GLFW window!");

	// Initialise OpenGL context
	glfwMakeContextCurrent(window);
	glfwSwapInterval(spec.VSync ? 1 : 0);

	// Initialise OpenGL
	const int version = gladLoadGL(glfwGetProcAddress);
	if (version == 0)
	{
		MM_ERROR("Failed to load OpenGL!");
		glfwTerminate();
		return false;
	}
	auto decodedVersion = GetGLADVersion(version);
	MM_INFO("Successfully loaded OpenGL {0}.{1}{2} via GLAD!", decodedVersion.first, decodedVersion.second,
	        spec.GLSettings.Core ? " (Core)" : "");

	// Basic GL Setup
	glViewport(0, 0, spec.Width, spec.Height);
	auto glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	auto renderer  = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	auto vendor    = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	MM_INFO("	Version: {0}", glVersion);
	MM_INFO("	GPU:     {0}", renderer);
	MM_INFO("	Vendor:  {0}", vendor);

	// Set OpenGL error callback
#ifndef MM_DIST
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLErrorCallback, nullptr);
#endif

	InitImGui();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410 core");

	// Init input
	delete Input::s_Instance;
	Input::s_Instance                                       = new GlfwInput();
	reinterpret_cast<GlfwInput*>(Input::s_Instance)->Window = window;

	// Setup GLFW event callbacks
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
		// Get data struct from the window
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		// Update data structs width and height values
		data.Width  = width;
		data.Height = height;

		// Create a resize event and dispatch it
		WindowResizeEvent e(width, height);
		data.EventCallback(e);
	});

	glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
	{
		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		WindowCloseEvent  e;
		data.EventCallback(e);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
		if (ImGui::GetIO().WantCaptureKeyboard)
			return;

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
		ImGui_ImplGlfw_CharCallback(window, codepoint);
		if (ImGui::GetIO().WantCaptureKeyboard)
			return;

		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		KeyTypedEvent     e(codepoint);
		data.EventCallback(e);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
	{
		ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
		if (ImGui::GetIO().WantCaptureMouse)
			return;

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
		ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
		if (ImGui::GetIO().WantCaptureMouse)
			return;

		const WindowData&  data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		MouseScrolledEvent e(xoffset, yoffset);
		data.EventCallback(e);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
	{
		ImGui::GetIO().AddMousePosEvent(static_cast<float>(xpos), static_cast<float>(ypos));
		if (ImGui::GetIO().WantCaptureMouse)
			return;

		const WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		MouseMovedEvent   e(static_cast<float>(xpos), static_cast<float>(ypos));
		data.EventCallback(e);
	});

	outWindow = new Window(spec, window);
	return true;
}

void Window::Run()
{
	static double lastFrametime;
	static float  printFPSTimer = 1;

	while (!glfwWindowShouldClose(m_Window))
	{
		const double frametime = glfwGetTime();
		m_UnscaledDeltaTime    = frametime - lastFrametime;
		m_UnscaledDeltaTime    = std::max(0.0, m_UnscaledDeltaTime);
		lastFrametime          = frametime;

		printFPSTimer -= static_cast<float>(GetDeltaTime());
		if (printFPSTimer <= 0)
		{
			MM_INFO("FPS: {0}", std::roundf(1 / static_cast<float>(m_UnscaledDeltaTime)));
			printFPSTimer = 1;
		}

		glfwPollEvents();

		for (Layer* layer : m_Layers)
			layer->OnUpdate(GetDeltaTime());

		Renderer::Prepare();

		for (Layer* layer : m_Layers)
			layer->OnRender();

		// ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::PushFont(s_NormalFont);
		for (Layer* layer : m_Layers)
			layer->OnImGuiRender();
		ImGui::PopFont();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		ImGui::GetIO().DisplaySize = ImVec2(static_cast<float>(m_WindowData.Width),
		                                    static_cast<float>(m_WindowData.Height));

		Input::UpdateInput();

		glfwSwapBuffers(m_Window);
	}
}

void Window::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<KeyPressedEvent>([](const KeyPressedEvent& keyPressedEvent)
	{
		Input::m_KeysDownNow[keyPressedEvent.GetKeyCode()] = true;
		return false;
	});
	dispatcher.Dispatch<KeyReleasedEvent>([](const KeyReleasedEvent& keyReleasedEvent)
	{
		Input::m_KeysDownNow[keyReleasedEvent.GetKeyCode()] = false;
		return false;
	});

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
	layer->SetWindow(this);
	layer->OnAttach();
}

void Window::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
	overlay->SetWindow(this);
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

void Window::Close() const
{
	glfwSetWindowShouldClose(m_Window, true);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_Window);
}

Window::Window(const WindowSpecification& spec, GLFWwindow* window)
	: m_Window(window)
{
	m_WindowData.Title         = spec.Title;
	m_WindowData.Width         = spec.Width;
	m_WindowData.Height        = spec.Height;
	m_WindowData.VSync         = spec.VSync;
	m_WindowData.EventCallback = BIND_EVENT_FN(Window::OnEvent);
	glfwSetWindowUserPointer(m_Window, &m_WindowData);
}

void Window::InitImGui()
{
	// Initialise ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding              = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	s_NormalFont = io.Fonts->AddFontFromFileTTF("Content/Fonts/OpenSans-Regular.ttf", 16.0f);
	s_BoldFont   = io.Fonts->AddFontFromFileTTF("Content/Fonts/OpenSans-Bold.ttf", 16.0f);
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
	Input::s_Instance = nullptr;

	// Shutdown ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// For now, assume there's only one window, so terminate on destruction.
	if (m_Window)
		glfwDestroyWindow(m_Window);
	glfwTerminate();
}
