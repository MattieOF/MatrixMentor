#include "mmpch.h"
#include "Tests/BasicLightingTest.h"

#include "imgui.h"
#include "Core/Rendering/Camera.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Rendering/Shaders/BasicLightingShader.h"
#include "Core/Utility/OBJLoader.h"

BasicLightingTest::BasicLightingTest()
	: m_Light(glm::vec3(0, 0, -20), glm::vec3(1.0f))
{ }

void BasicLightingTest::OnAttach()
{
	Test::OnAttach();

	m_Shader = BasicLightingShader::Create();
	m_Camera = CreateRef<Camera>();

	auto dragonModel = OBJLoader::LoadOBJ("Content/Models/StanfordDragon.obj");
	auto texture = CreateRef<Texture>("Content/Textures/White.png");
	auto texturedModel = CreateRef<TexturedModel>(dragonModel, texture);
	m_Entity = CreateRef<Entity>(Transform(glm::vec3(0, 0, -25)), texturedModel);
}

void BasicLightingTest::OnUpdate(double deltaSeconds)
{
	m_Camera->DoDefaultMovement(static_cast<float>(deltaSeconds));
}

void BasicLightingTest::OnRender()
{
	m_Shader->LoadLight(m_Light);
	Renderer::Begin(m_Camera.get());
	Renderer::RenderEntity(m_Entity.get(), m_Shader.get());
	Renderer::End();
}

bool BasicLightingTest::OnDrawTestPanel()
{
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
	
	return true;
}
