#include "mmpch.h"
#include "Core/Utility/DebugInfoLayer.h"

#include "imgui.h"
#include "Core/Window.h"
#include "Core/Input/Input.h"

void DebugInfoLayer::OnUpdate(double deltaSeconds)
{
	if (Input::IsKeyJustDown(MM_KEY_F2))
		m_IsVisible = !m_IsVisible;
}

void DebugInfoLayer::OnImGuiRender()
{
	if (!m_IsVisible)
		return;

	ImGui::Begin("Debug Info", &m_IsVisible);
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Text("Last frame time: %.3f ms", m_Window->GetUnscaledDeltaTime());
	ImGui::Text("Frame number: %d", m_Window->GetFrameNumber());
	float timescale = static_cast<float>(m_Window->GetTimeScale());
	if (ImGui::DragFloat("Time scale", &timescale, 0.02f, 0.01f, 10.0f))
		m_Window->SetTimeScale(timescale);
	ImGui::End();
}
