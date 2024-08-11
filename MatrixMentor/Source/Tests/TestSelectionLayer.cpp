#include "mmpch.h"

#include "imgui.h"
#include "Tests/TestSelectionLayer.h"

#include "Core/Window.h"
#include "Core/Input/Input.h"
#include "Core/Rendering/Renderer.h"
#include "Tests/PuppyCube.h"

TestSelectionLayer::TestSelectionLayer()
{
    m_Tests.push_back(reinterpret_cast<Test*>(new PuppyCube()));    
}

TestSelectionLayer::~TestSelectionLayer()
{
    for (const Test* test : m_Tests)
        delete test;
}

void TestSelectionLayer::OnImGuiRender()
{
    if (m_CurrentTest != nullptr)
        return;
    
    ImGui::Begin("Test Selection");

    ImGui::Text("Press Shift+Escape to quit a test.");
    for (Test* test : m_Tests)
    {
        if (ImGui::Button(test->GetTestName()))
        {
            m_CurrentTest = test->Create();
            m_Window->PushLayer(m_CurrentTest);
        }
        ImGui::SameLine();
        ImGui::Text(test->GetTestDescription());
    }

    ImGui::Separator();
    if (ImGui::Button("Quit"))
    {
        s_ShouldRestart = false;
        m_Window->Close();
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Quit the application. Can also press Escape.");
    ImGui::SameLine();
    if (ImGui::Button("Restart"))
    {
        s_ShouldRestart = true;
        m_Window->Close();
    }
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Restart the application (checking everything gets cleaned up). Can also press Shift+Escape.");
    ImGui::SameLine();
    
    ImGui::End();
}

void TestSelectionLayer::OnUpdate(double deltaSeconds)
{
    if (m_CurrentTest)
    {
        if (Input::IsKeyJustDown(MM_KEY_ESCAPE) && Input::IsKeyDown(MM_KEY_LEFT_SHIFT))
        {
            Renderer::ResetClearColor();
            m_Window->PopLayer(m_CurrentTest);
            delete m_CurrentTest;
            m_CurrentTest = nullptr;
        }

        if (Input::IsKeyJustDown(MM_KEY_R))
        {
            s_ShouldRestart = !s_ShouldRestart;
            if (s_ShouldRestart)
                MM_INFO("The application will now restart on quit.");
            else
                MM_INFO("The application will now shutdown fully on quit.");
        }
    } else
    {
        if (Input::IsKeyJustDown(MM_KEY_ESCAPE))
        {
            s_ShouldRestart = Input::IsKeyDown(MM_KEY_LEFT_SHIFT);
            m_Window->Close();
        }
    }
}
