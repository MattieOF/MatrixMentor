#pragma once

#include "Core/Layer.h"
#include "Core/Events/ApplicationEvent.h"

class BaseOpenGLLayer : public Layer
{
	void OnEvent(Event& event) override;

	bool OnResize(WindowResizeEvent& e);
};
