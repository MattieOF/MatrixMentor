#include "mmpch.h"

#include "Core/Rendering/Shaders/BasicSpecularLightingShader.h"
#include "Core/Rendering/Renderer.h"

#include "Core/Rendering/Lighting/Light.h"
#include "Core/Rendering/Material/Material.h"

BasicSpecularLightingShader::BasicSpecularLightingShader()
	: StaticShader("Basic Specular Lighting Shader")
{ }

void BasicSpecularLightingShader::BindAttributes()
{
	StaticShader::BindAttributes();
}

void BasicSpecularLightingShader::GetUniformLocations()
{
	StaticShader::GetUniformLocations();

	GetUniformLocation("lightPosition");
	GetUniformLocation("lightColor");
	GetUniformLocation("shineDamper");
	GetUniformLocation("reflectivity");
}

void BasicSpecularLightingShader::LoadLight(const Light& light) const
{
	Renderer::BindShader(this);
	SetUniformVec3("lightPosition", light.GetPosition());
	SetUniformVec3("lightColor", light.GetColor());
}

void BasicSpecularLightingShader::LoadMaterial(const Material& material) const
{
	SetUniform1f("shineDamper", material.ShineDamper);
	SetUniform1f("reflectivity", material.Reflectivity);
}

void BasicSpecularLightingShader::Setup()
{
	AddStageFromFile(GL_VERTEX_SHADER, "Content/Shaders/BasicSpecularVertex.glsl");
	AddStageFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/BasicSpecularFragment.glsl");
	LinkProgram();
}
