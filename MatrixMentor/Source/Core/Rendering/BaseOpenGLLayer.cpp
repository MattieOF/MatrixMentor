#include "mmpch.h"

#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Rendering/Shaders/ShaderProgram.h"

#include "Core/Events/Events.h"
#include <gl/GL.h>

BaseOpenGLLayer::BaseOpenGLLayer()
{
	m_ShaderTest = ShaderProgram::CreateShaderProgram("Test Shader");
	m_ShaderTest->BindAttribute(0, "inPosition");
	m_ShaderTest->AddStageFromFile(GL_VERTEX_SHADER, "Content/Shaders/BasicVertex.glsl");
	m_ShaderTest->AddStageFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/BasicFragment.glsl");
	//m_ShaderTest->AddStageFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/SecondFragmentTest.glsl");
	m_ShaderTest->CompileAndLink();
	m_ShaderTest->Bind();
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
