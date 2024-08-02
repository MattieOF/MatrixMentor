#pragma once

#include "Core/Rendering/Shaders/ShaderProgram.h"

class StaticShader :
    public ShaderProgram
{
public:
    StaticShader();

    void BindAttributes() override;
};
