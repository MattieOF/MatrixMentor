#include "mmpch.h"
#include "Tests/BasicSpecularLightingTest.h"

#include "imgui.h"
#include "Core/Window.h"
#include "Core/Rendering/Camera.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Rendering/Shaders/BasicSpecularLightingShader.h"
#include "Core/Utility/OBJLoader.h"

BasicSpecularLightingTest::BasicSpecularLightingTest()
	: m_Light(glm::vec3(0, 0, -20), glm::vec3(1.0f))
{ }

void BasicSpecularLightingTest::OnAttach()
{
	Test::OnAttach();
	
	m_PanelVisible = true;

	m_Shader = BasicSpecularLightingShader::Create();
	m_Camera = CreateRef<Camera>();

	auto dragonModel = OBJLoader::LoadOBJ("Content/Models/StanfordDragon.obj");
	auto texture = CreateRef<Texture>("Content/Textures/White.png");
	auto texturedModel = CreateRef<TexturedModel>(dragonModel, texture);
	m_Entity = CreateRef<Entity>(Transform(glm::vec3(0, 0, -25)), texturedModel);
	m_Camera->GetTransform().Position = glm::vec3(0, 4, -15);

	m_Material.Reflectivity = 1.0f;
	m_Material.ShineDamper = 10.0f;
	m_Light.SetColor(glm::vec3(0.8f, 0.2f, 0.2f));
}

void BasicSpecularLightingTest::OnUpdate(double deltaSeconds)
{
	m_Entity->GetTransform().Rotation += glm::vec3(0.0f, m_RotationSpeed * static_cast<float>(deltaSeconds), 0.0f);
	
	m_Camera->DoDefaultMovement(static_cast<float>(deltaSeconds));
}

void BasicSpecularLightingTest::OnRender()
{
	m_Shader->LoadLight(m_Light);
	m_Shader->LoadMaterial(m_Material);
	Renderer::Begin(m_Camera.get());
	Renderer::RenderEntity(m_Entity.get(), m_Shader.get());
	Renderer::End();
}

bool BasicSpecularLightingTest::OnDrawTestPanel()
{
	ImGui::PushFont(Window::s_BoldFont);
	ImGui::Text("Dragon Controls");
	ImGui::PopFont();

	ImGui::DragFloat("Rotation Speed", &m_RotationSpeed, 5.f, -150, 150);
	ImGui::SameLine();
	if (ImGui::Button("Reset Rotation"))
	{
		m_RotationSpeed = 0.0f;
		m_Entity->GetTransform().Rotation = glm::vec3(0.0f);
	}
	
	ImGui::PushFont(Window::s_BoldFont);
	ImGui::Text("Light Properties");
	ImGui::PopFont();
	
	glm::vec3 lightColour = m_Light.GetColor();
	if (ImGui::ColorPicker3("Light Colour", &lightColour.x))
	{
		m_Light.SetColor(lightColour);
	}
	glm::vec3 position = m_Light.GetPosition();
	if (ImGui::DragFloat3("Light Position", &position.x, 0.1f))
	{
		m_Light.SetPosition(position);
	}

	ImGui::PushFont(Window::s_BoldFont);
	ImGui::Text("Material Properties");
	ImGui::PopFont();

	ImGui::DragFloat("Reflectivity", &m_Material.Reflectivity, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Shine Damper", &m_Material.ShineDamper, 0.01f, 0.0f, 20.0f);
	
	return true;
}
