#pragma once

#include "Core/Rendering/Shaders/ShaderProgram.h"

class StaticShader :
    public ShaderProgram
{
public:
    StaticShader();

    void BindAttributes() override;
    void GetUniformLocations() override;

    void LoadTransformationMatrix(const glm::mat4& matrix) const;
    void LoadProjectionMatrix(const glm::mat4& matrix) const;
};
