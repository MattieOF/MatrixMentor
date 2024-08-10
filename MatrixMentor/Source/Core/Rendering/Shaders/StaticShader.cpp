#include "mmpch.h"

#include "Core/Rendering/Shaders/StaticShader.h"

StaticShader::StaticShader() : ShaderProgram("Static Shader")
{
	AddStageFromFile(GL_VERTEX_SHADER, "Content/Shaders/StaticVertex.glsl");
	AddStageFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/StaticFragment.glsl");
    LinkProgram();
}

void StaticShader::BindAttributes()
{
	BindAttribute(0, "inPosition");
	BindAttribute(1, "inUV");
}

void StaticShader::GetUniformLocations()
{
	// Cache uniform locations
	GetUniformLocation("transformMatrix");
	GetUniformLocation("projectionMatrix");
	GetUniformLocation("viewMatrix");
}

void StaticShader::LoadTransformationMatrix(const glm::mat4& matrix) const
{
	SetUniformMatrix4f("transformMatrix", matrix);
}

void StaticShader::LoadProjectionMatrix(const glm::mat4& matrix) const
{
	SetUniformMatrix4f("projectionMatrix", matrix);
}

void StaticShader::LoadViewMatrix(const glm::mat4& matrix) const
{
	SetUniformMatrix4f("viewMatrix", matrix);
}
