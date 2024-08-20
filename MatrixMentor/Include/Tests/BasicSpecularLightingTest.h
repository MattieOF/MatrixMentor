#pragma once

#include "Core/Rendering/Lighting/Light.h"
#include "Core/Rendering/Material/Material.h"
#include "Tests/Test.h"

class BasicSpecularLightingShader;
class Entity;
class Camera;

class BasicSpecularLightingTest : public Test
{
public:
	BasicSpecularLightingTest();
	
	void OnAttach() override;
	void OnUpdate(double deltaSeconds) override;
	void OnRender() override;
	bool OnDrawTestPanel() override;
	
	Test* Create() override { return new BasicSpecularLightingTest(); }
	const char* GetTestName() const override { return "Basic Specular Lighting Test"; }
	const char* GetTestDescription() const override { return "Basic specular lighting"; }

private:
	Light m_Light;
	Material m_Material;
	
	Ref<BasicSpecularLightingShader> m_Shader;
	Ref<Camera> m_Camera;
	Ref<Entity> m_Entity;

	float m_RotationSpeed = 50.0f;
};
