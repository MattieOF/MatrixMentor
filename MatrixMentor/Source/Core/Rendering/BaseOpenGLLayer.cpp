#include "mmpch.h"

#include "Core/Rendering/BaseOpenGLLayer.h"

#include "Core/Events/Events.h"
#include <gl/GL.h>

void BaseOpenGLLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(BaseOpenGLLayer::OnResize));
}

bool BaseOpenGLLayer::OnResize(WindowResizeEvent& e)
{
	glViewport(0, 0, static_cast<int>(e.GetWidth()), static_cast<int>(e.GetHeight()));
	return false;
}
