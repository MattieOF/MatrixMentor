#include "mmpch.h"

#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Rendering/Shaders/ShaderProgram.h"

#include "Core/Events/Events.h"
#include <gl/GL.h>

BaseOpenGLLayer::BaseOpenGLLayer()
{
	m_ShaderTest = ShaderProgram::LoadShaderFromFiles("Test Shader", "Content/Shaders/BasicVertex.glsl", "Content/Shaders/BasicFragment.glsl");
	m_ShaderTest->BindAttribute(0, "inPosition");
	m_ShaderTest->Bind();
}

void BaseOpenGLLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& windowResizeEvent) { return OnResize(windowResizeEvent); });
}

bool BaseOpenGLLayer::OnResize(const WindowResizeEvent& e)
{
	glViewport(0, 0, static_cast<int>(e.GetWidth()), static_cast<int>(e.GetHeight()));
	return false;
}
