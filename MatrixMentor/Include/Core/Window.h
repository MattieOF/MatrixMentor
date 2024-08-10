#pragma once

#include "Layer.h"

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

struct WindowData
{
	using EventCallbackFn = std::function<void(Event&)>;

	std::string Title = "Window";
	uint32_t Width = 1280, Height = 600;
	bool VSync = true;

	EventCallbackFn EventCallback;
};

class Window
{
public:
	Window() = delete;
	virtual ~Window();

	static bool Create(const WindowSpecification& spec, Window*& outWindow);

	void Run();
	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopLayer(Layer* layer);
	void PopOverlay(Layer* overlay);

	FORCEINLINE virtual void SetVSync(bool enabled);
	FORCEINLINE [[nodiscard]] virtual bool IsVSync() const;

	FORCEINLINE void SetClipboardText(const char* text) const;
	[[nodiscard]] FORCEINLINE const char* GetClipboardText() const;

	FORCEINLINE void SetWindowTitle(std::string_view newTitle);

	[[nodiscard]] virtual float GetAspectRatio() const { return static_cast<float>(m_WindowData.Width) / static_cast<float>(m_WindowData.Height); }

	[[nodiscard]] virtual GLFWwindow* GetNativeWindow() const { return m_Window; }

	// Delta time functions
	[[nodiscard]] double GetDeltaTime() const         { return m_UnscaledDeltaTime * m_TimeScale; }
	[[nodiscard]] double GetUnscaledDeltaTime() const { return m_UnscaledDeltaTime; }
	[[nodiscard]] double GetTimeScale() const         { return m_TimeScale; }
	void SetTimeScale(double newTimeScale)            { m_TimeScale = newTimeScale; }

	void Close() const;
	FORCEINLINE bool ShouldClose() const;

private:
	Window(const WindowSpecification& spec, GLFWwindow* window);

	GLFWwindow* m_Window = nullptr;

	std::vector<Layer*> m_Layers;
	int m_LayerStackInsert = 0;

	WindowData m_WindowData;

	double m_UnscaledDeltaTime = 0, m_TimeScale = 1;
};
