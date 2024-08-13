#include "mmpch.h"
#include "Tests/BYOTCubeTest.h"

#include "imgui.h"
#include "Core/Window.h"
#include "Core/Entity/Transform.h"
#include "Core/Rendering/Camera.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/Texture.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Rendering/Shaders/StaticShader.h"
#include "Core/Utility/OBJLoader.h"
#include "Vendor/tinyfiledialogs.h"

#define TEXTURE_PATH_BUFFER_SIZE 512

void BYOTCubeTest::OnAttach()
{
	m_PanelVisible = true;
	
	//auto model = OBJLoader::LoadOBJ("Content/Models/Test.obj");
	auto model = OBJLoader::LoadOBJ("Content/Models/Cube.obj");
	if (!model)
	{
		MM_ERROR("OBJLoadingTest: Failed to load obj!");
		DestroySelf();
	}

	//auto texture = CreateRef<Texture>("Content/Textures/TestModelTexture.png");
	auto texture = CreateRef<Texture>("Content/Textures/PUPPY.jpg");
	if (texture->GetWidth() == 0)
	{
		MM_ERROR("OBJLoadingTest: Failed to load texture!");
		DestroySelf();
	}
	
	m_Camera = CreateRef<Camera>();
	m_Shader = CreateRef<StaticShader>();
	m_Entity = CreateRef<Entity>(Transform(glm::vec3(0, 0, -5)), CreateRef<TexturedModel>(model, texture));
}

void BYOTCubeTest::OnUpdate(double deltaSeconds)
{
	m_Camera->DoDefaultMovement(static_cast<float>(deltaSeconds));
	m_Entity->GetTransform().Rotation.y += static_cast<float>(deltaSeconds) * 10;
}

void BYOTCubeTest::OnRender()
{
	Renderer::Begin(m_Camera.get());
	Renderer::RenderEntity(m_Entity.get(), m_Shader.get());
	Renderer::End();
}

bool BYOTCubeTest::OnDrawTestPanel()
{
	ImGui::PushFont(Window::s_BoldFont);
	ImGui::Text("Settings");
	ImGui::PopFont();
	ImGui::DragFloat3("Cube Scale", &m_Entity->GetTransform().Scale.x, 0.01f, 0.1f, 10.f);
	ImGui::Separator();
	ImGui::PushFont(Window::s_BoldFont);
	ImGui::Text("Select a texture:");
	ImGui::PopFont();
	
	static char texturePath[TEXTURE_PATH_BUFFER_SIZE] = "Content/Textures/";
	
	ImGui::Text("File path: ");
	ImGui::SameLine();
	ImGui::InputText("##", texturePath, TEXTURE_PATH_BUFFER_SIZE);
	ImGui::SameLine();
	
	if (ImGui::Button("..."))
	{
		const char* filterPatterns[1] = { "*.png;*.jpg;*.jpeg" };
		char* result = tinyfd_openFileDialog("Select a texture", nullptr, 1, filterPatterns, "Image Files", 0);
		if (result != nullptr)
		{
			strcpy_s(texturePath, TEXTURE_PATH_BUFFER_SIZE, result);
			LoadTexture(texturePath);
		}
	}
	
	if (ImGui::Button("Load"))
	{
		LoadTexture(texturePath);
	}

	return true;
}

void BYOTCubeTest::LoadTexture(const char* texturePath) const
{
	Ref<Texture> newTexture = CreateRef<Texture>(texturePath);
	if (newTexture->GetWidth() == 0)
	{
		MM_ERROR("BYOTCubeTest: Failed to load texture!");
		return;
	}
	m_Entity->GetModel()->SetTexture(newTexture);
}
