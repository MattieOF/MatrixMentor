#pragma once
#include "Test.h"
#include "Core/Layer.h"

class TestSelectionLayer : public Layer
{
public:
    TestSelectionLayer();
    ~TestSelectionLayer() override;
    
    void OnImGuiRender() override;
    void OnUpdate(double deltaSeconds) override;

private:
    Test* m_CurrentTest = nullptr;
    std::vector<Test*> m_Tests;
};
