#pragma once

#include "StaticShader.h"

class Material;
class Light;

class BasicSpecularLightingShader : public StaticShader
{
public:
	BasicSpecularLightingShader();
	
	static Ref<BasicSpecularLightingShader> Create() { auto shader = CreateRef<BasicSpecularLightingShader>(); shader->Setup(); return shader; }

	void BindAttributes() override;
	void GetUniformLocations() override;

	void LoadLight(const Light& light) const;
	void LoadMaterial(const Material& material) const;

protected:
	void Setup() override;
};
