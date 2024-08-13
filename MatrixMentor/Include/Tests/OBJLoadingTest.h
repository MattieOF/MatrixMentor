#pragma once

#include "Test.h"

class StaticShader;
class Camera;
class Entity;
class RawModel;

class OBJLoadingTest : public Test
{
public:
	void OnAttach() override;
	void OnUpdate(double deltaSeconds) override;
	void OnRender() override;

	Test* Create() override { return new OBJLoadingTest(); }
	const char* GetTestDescription() const override { return "Loads a basic .obj model"; }
	const char* GetTestName() const override { return "OBJ Loading Test"; }

private:
	Ref<StaticShader> m_Shader;
	Ref<Camera> m_Camera;
	Ref<Entity> m_Entity;
};
