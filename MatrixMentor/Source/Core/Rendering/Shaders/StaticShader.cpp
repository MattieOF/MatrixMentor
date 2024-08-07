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
}

void StaticShader::LoadTransformationMatrix(const glm::mat4& matrix) const
{
	SetUniformMatrix4f("transformMatrix", matrix);
}
