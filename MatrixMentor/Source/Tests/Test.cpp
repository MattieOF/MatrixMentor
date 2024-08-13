#include "mmpch.h"
#include "Tests/Test.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "Core/Window.h"
#include "Core/Input/Input.h"
#include "Tests/TestSelectionLayer.h"

void Test::OnImGuiRender()
{
	if (Input::IsKeyJustDown(MM_KEY_F1))
		m_PanelVisible = !m_PanelVisible;
	
	if (!m_PanelVisible)
		return;

	ImGui::Begin(GetTestName(), &m_PanelVisible, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
	ImGui::PushFont(Window::s_BoldFont);
	ImGui::Text("%s", GetTestName());
	ImGui::PopFont();
	ImGui::Text("%s", GetTestDescription());
	ImGui::Separator();
	if (OnDrawTestPanel())
		ImGui::Separator();
	if (ImGui::Button("Return to Test Selection"))
		DestroySelf();
	
	ImGui::End();
}

bool Test::OnDrawTestPanel()
{
	return false;
}

void Test::DestroySelf()
{
	MM_ASSERT_ERROR(m_TestSelectionLayer, "Test::PopSelf called without a valid TestSelectionLayer!");

	m_TestSelectionLayer->DestroyCurrentTest();
}
