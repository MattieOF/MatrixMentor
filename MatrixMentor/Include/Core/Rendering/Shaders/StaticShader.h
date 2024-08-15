#pragma once

#include "Core/Rendering/Shaders/ShaderProgram.h"

class StaticShader :
	public ShaderProgram
{
public:
	StaticShader();
	StaticShader(std::string_view name);

	static Ref<StaticShader> Create() { auto shader = CreateRef<StaticShader>(); shader->Setup(); return shader; }

	void BindAttributes() override;
	void GetUniformLocations() override;

	void LoadTransformationMatrix(const glm::mat4& matrix) const;
	void LoadProjectionMatrix(const glm::mat4& matrix) const;
	void LoadViewMatrix(const glm::mat4& matrix) const;

protected:
	virtual void Setup();
};
