#include "mmpch.h"
#include "Tests/PuppyCube.h"

#include "imgui.h"
#include "Core/Entity/Entity.h"
#include "Core/Input/Input.h"
#include "Core/Rendering/Camera.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/Texture.h"
#include "Core/Rendering/Shaders/StaticShader.h"

PuppyCube::PuppyCube()
{
	m_DebugName = "Puppy Cube Test";
}

const char* PuppyCube::GetTestName() const
{
	return "Puppy Cube";
}

const char* PuppyCube::GetTestDescription() const
{
	return "Spinning cube!";
}

Test* PuppyCube::Create()
{
	return new PuppyCube();
}

void PuppyCube::OnAttach()
{
	std::vector<float> vertices = {
		-0.5f,0.5f,-0.5f,	
		-0.5f,-0.5f,-0.5f,	
		0.5f,-0.5f,-0.5f,	
		0.5f,0.5f,-0.5f,		
			
		-0.5f,0.5f,0.5f,	
		-0.5f,-0.5f,0.5f,	
		0.5f,-0.5f,0.5f,	
		0.5f,0.5f,0.5f,
			
		0.5f,0.5f,-0.5f,	
		0.5f,-0.5f,-0.5f,	
		0.5f,-0.5f,0.5f,	
		0.5f,0.5f,0.5f,
			
		-0.5f,0.5f,-0.5f,	
		-0.5f,-0.5f,-0.5f,	
		-0.5f,-0.5f,0.5f,	
		-0.5f,0.5f,0.5f,
			
		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,
			
		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f
	};

	std::vector<float> texCoords = {
		0, 0,
		0, 1,
		1, 1,
		1, 0,			
		0, 0,
		0, 1,
		1, 1,
		1, 0,			
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	std::vector<uint32_t> indices = {
		0, 1, 3,
		3, 1, 2,
		4, 5, 7,
		7, 5, 6,
		8, 9, 11,
		11, 9, 10,
		12, 13, 15,
		15, 13, 14,
		16, 17, 19,
		19, 17, 18,
		20, 21, 23,
		23, 21, 22
	};

	auto rectangleMesh = CreateRef<RawModel>(vertices, texCoords, indices);
	auto testTexture = CreateRef<Texture>("Content/Textures/PUPPY.jpg");
	auto texturedModel = CreateRef<TexturedModel>(rectangleMesh, testTexture);
	m_TestEntity = CreateRef<Entity>(texturedModel);
	m_TestEntity->GetTransform().Position = glm::vec3(0, 0, -1);

	m_Camera = CreateRef<Camera>();

	m_StaticShader = CreateRef<StaticShader>();

	Renderer::SetClearColor(glm::vec4(0.392f, 0.584f, 0.929f, 1.f)); // Cornflower blue
}

void PuppyCube::OnRender()
{
	Renderer::Begin(m_Camera.get());
	Renderer::RenderEntity(m_TestEntity.get(), m_StaticShader.get());
	Renderer::End();
}

void PuppyCube::OnImGuiRender()
{
	ImGui::Begin("Puppy Cube Test");

	ImGui::Text("A/D: Rotate cube");
	ImGui::Text("Left Shift: Speed up rotation");
	ImGui::Text("W/S: Move cube along Z axis");
	ImGui::Text("Q/E: Scale cube");
	ImGui::Text("Arrow keys: Move camera");
	ImGui::Separator();
	if (ImGui::Button("Return to test selection"))
		DestroySelf();

	ImGui::End();
}

void PuppyCube::OnUpdate(double deltaSeconds)
{
	if (Input::IsKeyDown(MM_KEY_A))
		m_TestEntity->GetTransform().Rotation.z += static_cast<float>(deltaSeconds) * 10;
	if (Input::IsKeyDown(MM_KEY_D))
		m_TestEntity->GetTransform().Rotation.z -= static_cast<float>(deltaSeconds) * 10;

	float speed = 5;
	if (Input::IsKeyDown(MM_KEY_LEFT_SHIFT))
		speed *= 4;
	m_TestEntity->GetTransform().Rotation += glm::vec3(speed * static_cast<float>(deltaSeconds));

	if (Input::IsKeyDown(MM_KEY_W))
		m_TestEntity->GetTransform().Position.z += static_cast<float>(deltaSeconds);
	if (Input::IsKeyDown(MM_KEY_S))
		m_TestEntity->GetTransform().Position.z -= static_cast<float>(deltaSeconds);
		
	if (Input::IsKeyDown(MM_KEY_Q))
		m_TestEntity->GetTransform().Scale -= static_cast<float>(deltaSeconds) / 2;
	if (Input::IsKeyDown(MM_KEY_E))
		m_TestEntity->GetTransform().Scale += static_cast<float>(deltaSeconds) / 2;

	if (Input::IsKeyDown(MM_KEY_LEFT))
		m_Camera->GetTransform().Position.x -= static_cast<float>(deltaSeconds);
	if (Input::IsKeyDown(MM_KEY_RIGHT))
		m_Camera->GetTransform().Position.x += static_cast<float>(deltaSeconds);
	if (Input::IsKeyDown(MM_KEY_UP))
		m_Camera->GetTransform().Position.y += static_cast<float>(deltaSeconds);
	if (Input::IsKeyDown(MM_KEY_DOWN))
		m_Camera->GetTransform().Position.y -= static_cast<float>(deltaSeconds);
}
