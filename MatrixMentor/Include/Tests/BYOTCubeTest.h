﻿#pragma once

#include "Test.h"

class Entity;
class Camera;
class StaticShader;

class BYOTCubeTest : public Test
{
public:
	void OnAttach() override;
	void OnUpdate(double deltaSeconds) override;
	void OnRender() override;
	bool OnDrawTestPanel() override;
	
	Test* Create() override { return new BYOTCubeTest(); }
	const char* GetTestName() const override { return "BYOT Cube"; }
	const char* GetTestDescription() const override { return "Cube with a dynamic texture"; }

private:
	void LoadTexture(const char* texturePath) const;
	
	Ref<StaticShader> m_Shader;
	Ref<Camera> m_Camera;
	Ref<Entity> m_Entity;
};
