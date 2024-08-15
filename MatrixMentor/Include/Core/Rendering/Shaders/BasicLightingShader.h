#pragma once

#include "StaticShader.h"

class Light;

class BasicLightingShader : public StaticShader
{
public:
	BasicLightingShader();
	
	static Ref<BasicLightingShader> Create() { auto shader = CreateRef<BasicLightingShader>(); shader->Setup(); return shader; }

	void BindAttributes() override;
	void GetUniformLocations() override;

	void LoadLight(const Light& light) const;

protected:
	void Setup() override;
};
