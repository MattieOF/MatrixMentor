#include "mmpch.h"

#include "Core/Rendering/Shaders/BasicLightingShader.h"
#include "Core/Rendering/Renderer.h"

#include "Core/Rendering/Lighting/Light.h"

BasicLightingShader::BasicLightingShader()
	: StaticShader("Basic Lighting Shader")
{ }

void BasicLightingShader::BindAttributes()
{
	StaticShader::BindAttributes();
}

void BasicLightingShader::GetUniformLocations()
{
	StaticShader::GetUniformLocations();

	GetUniformLocation("lightPosition");
	GetUniformLocation("lightColor");
}

void BasicLightingShader::LoadLight(const Light& light) const
{
	Renderer::BindShader(this);
	SetUniformVec3("lightPosition", light.GetPosition());
	SetUniformVec3("lightColor", light.GetColor());
}

void BasicLightingShader::Setup()
{
	AddStageFromFile(GL_VERTEX_SHADER, "Content/Shaders/BasicLightingVertex.glsl");
	AddStageFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/BasicLightingFragment.glsl");
	LinkProgram();
}
