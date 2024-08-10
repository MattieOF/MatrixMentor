#pragma once

#include "Core/Layer.h"
#include "Core/Events/ApplicationEvent.h"

class ShaderProgram;

class BaseOpenGLLayer : public Layer
{
	void OnAttach() override;
	void OnEvent(Event& event) override;
	bool OnResize(const WindowResizeEvent& e) const;
	void OnDetach() override;
};
