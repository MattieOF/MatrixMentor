#pragma once

#include "Events/Event.h"

class Window;

class Layer
{
public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer();

	virtual void OnAttach() { }
	virtual void OnDetach() { }
	virtual void OnUpdate(double deltaSeconds) { }
	virtual void OnImGuiRender() { }
	virtual void OnRender() { }
	virtual void OnEvent(Event& event) { }

	[[nodiscard]] FORCEINLINE const std::string& GetName() const { return m_DebugName; }

	FORCEINLINE void SetWindow(Window* window) { m_Window = window; }

protected:
	Window* m_Window;

private:
	std::string m_DebugName;
};
