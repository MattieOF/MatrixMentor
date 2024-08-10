#include "mmpch.h"

#include <gl/GL.h>

#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Events/Events.h"
#include "Core/Window.h"
#include "Core/Rendering/Renderer.h"

void BaseOpenGLLayer::OnAttach()
{
	Renderer::SetAspectRatio(m_Window->GetAspectRatio());
}

void BaseOpenGLLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>([this](const WindowResizeEvent& windowResizeEvent) { return OnResize(windowResizeEvent); });
}

bool BaseOpenGLLayer::OnResize(const WindowResizeEvent& e) const
{
	glViewport(0, 0, static_cast<int>(e.GetWidth()), static_cast<int>(e.GetHeight()));
	Renderer::SetAspectRatio(m_Window->GetAspectRatio());
	return false;
}

void BaseOpenGLLayer::OnDetach()
{
	Renderer::Shutdown();
}
