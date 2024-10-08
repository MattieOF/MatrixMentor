﻿#pragma once

#include "Tests/Test.h"

class Entity;
class Camera;
class StaticShader;

class PuppyCube : public Test
{
public:
	PuppyCube();

	[[nodiscard]] const char* GetTestName() const override;
	[[nodiscard]] const char* GetTestDescription() const override;
	Test*                     Create() override;

	void OnAttach() override;
	void OnUpdate(double deltaSeconds) override;
	void OnRender() override;
	bool OnDrawTestPanel() override;

private:
	Ref<StaticShader> m_StaticShader;
	Ref<Camera>       m_Camera;
	Ref<Entity>       m_TestEntity;
};
