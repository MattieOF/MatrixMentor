#pragma once

#include "Core/Rendering/Lighting/Light.h"
#include "Tests/Test.h"

class Light;
class BasicLightingShader;
class Entity;
class Camera;

class BasicLightingTest : public Test
{
public:
	BasicLightingTest();
	
	void OnAttach() override;
	void OnUpdate(double deltaSeconds) override;
	void OnRender() override;
	bool OnDrawTestPanel() override;
	
	Test* Create() override { return new BasicLightingTest(); }
	const char* GetTestName() const override { return "Basic Lighting Test"; }
	const char* GetTestDescription() const override { return "Basic per-pixel lighing shader test"; }

private:
	Light m_Light;
	
	Ref<BasicLightingShader> m_Shader;
	Ref<Camera> m_Camera;
	Ref<Entity> m_Entity;
};
