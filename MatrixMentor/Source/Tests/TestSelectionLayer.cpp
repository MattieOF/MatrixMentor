#include "mmpch.h"

#include "imgui.h"
#include "Core/Window.h"
#include "Tests/TestSelectionLayer.h"

void TestSelectionLayer::OnImGuiRender()
{
    ImGui::Begin("Test Selection");
    ImGui::Text("Hello, ImGui!");
    if (ImGui::Button("fuck off"))
        m_Window->Close();
    ImGui::SameLine();
    ImGui::Checkbox("Should restart", &s_ShouldRestart);
    ImGui::End();
}
