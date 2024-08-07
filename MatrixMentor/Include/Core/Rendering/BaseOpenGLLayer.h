#pragma once

#include "Core/Layer.h"
#include "Core/Events/ApplicationEvent.h"

class ShaderProgram;

class BaseOpenGLLayer : public Layer
{
public:
	BaseOpenGLLayer();

private:
	void OnEvent(Event& event) override;
	static bool OnResize(const WindowResizeEvent& e);
};
