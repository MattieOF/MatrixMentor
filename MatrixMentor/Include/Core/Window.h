#pragma once

// Forward defs
struct GLFWwindow;

struct GLSettings
{
	int Major = 3, Minor = 2;
	bool Core = true;
};

struct WindowSpecification
{
	std::string Title;
	int Width = 1280, Height = 600;
	bool VSync = false;
	bool Resizeable = true;
	bool Centered = true;
	GLSettings GLSettings;
};

class Window
{
public:
	Window() = delete;
	~Window();

	static bool Create(const WindowSpecification& spec, Window*& outWindow);

	void Run();

	FORCEINLINE bool ShouldClose() const;

private:
	Window(GLFWwindow* window);

	GLFWwindow* m_Window = nullptr;
};
