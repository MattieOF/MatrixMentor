#include "mmpch.h"

#include "imgui.h"
#include "Tests/TestSelectionLayer.h"

#include "Core/Window.h"
#include "Core/Input/Input.h"
#include "Core/Rendering/Renderer.h"
#include "Tests/BYOTCubeTest.h"
#include "Tests/OBJLoadingTest.h"
#include "Tests/PuppyCube.h"

TestSelectionLayer::TestSelectionLayer()
{
	m_Tests.push_back(new PuppyCube());
	m_Tests.push_back(new BYOTCubeTest());
	m_Tests.push_back(new OBJLoadingTest());
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
	ImGui::Text("F1 to toggle test info panel.");
	ImGui::Separator();

	ImGui::PushFont(Window::s_BoldFont);
	ImGui::Text("Available tests:");
	ImGui::PopFont();
	for (Test* test : m_Tests)
	{
		if (ImGui::Button(test->GetTestName()))
		{
			m_CurrentTest                       = test->Create();
			m_CurrentTest->m_TestSelectionLayer = this;
			m_Window->PushLayer(m_CurrentTest);
		}
		ImGui::SameLine();
		ImGui::Text("%s", test->GetTestDescription());
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
		ImGui::SetTooltip(
			"Restart the application (checking everything gets cleaned up). Can also press Shift+Escape.");
	ImGui::SameLine();

	ImGui::End();
}

void TestSelectionLayer::OnUpdate(double deltaSeconds)
{
	if (m_CurrentTest &&
		m_DestroyCurrentTestFrame != 0 &&
		m_Window->GetFrameNumber() >= m_DestroyCurrentTestFrame)
	{
		delete m_CurrentTest;
		m_CurrentTest = nullptr;
		m_DestroyCurrentTestFrame = 0;
	}
	
	if (m_CurrentTest)
	{
		if (Input::IsKeyJustDown(MM_KEY_ESCAPE) && Input::IsKeyDown(MM_KEY_LEFT_SHIFT))
			DestroyCurrentTest();

		if (Input::IsKeyJustDown(MM_KEY_R))
		{
			s_ShouldRestart = !s_ShouldRestart;
			if (s_ShouldRestart)
				MM_INFO("The application will now restart on quit.");
			else
				MM_INFO("The application will now shutdown fully on quit.");
		}
	}
	else
	{
		if (Input::IsKeyJustDown(MM_KEY_ESCAPE))
		{
			s_ShouldRestart = Input::IsKeyDown(MM_KEY_LEFT_SHIFT);
			m_Window->Close();
		}
	}
}

void TestSelectionLayer::DestroyCurrentTest()
{
	Renderer::ResetClearColor();
	m_Window->PopLayer(m_CurrentTest);
	// Can't delete the test here because the frame isn't over - the pointer is still in use
	// Instead, we'll set a flag to delete it in the next frame's update
	m_DestroyCurrentTestFrame = m_Window->GetFrameNumber() + 1;
}
