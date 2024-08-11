#pragma once
#include "Core/Layer.h"

class Test : public Layer
{
public:
    [[nodiscard]] virtual const char* GetTestName() const = 0;
    [[nodiscard]] virtual const char* GetTestDescription() const = 0;
    virtual Test* Create() = 0;
};
