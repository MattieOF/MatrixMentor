#include "mmpch.h"

#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Input/Input.h"

#include "Core/Events/Events.h"
#include <gl/GL.h>

BaseOpenGLLayer::BaseOpenGLLayer()
{
}

void BaseOpenGLLayer::OnUpdate(double deltaSeconds)
{
}

void BaseOpenGLLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>([](const WindowResizeEvent& windowResizeEvent) { return OnResize(windowResizeEvent); });
}

bool BaseOpenGLLayer::OnResize(const WindowResizeEvent& e)
{
	glViewport(0, 0, static_cast<int>(e.GetWidth()), static_cast<int>(e.GetHeight()));
	return false;
}
