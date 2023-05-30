#pragma once

#include "Events/Event.h"

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
private:
	std::string m_DebugName;
};
