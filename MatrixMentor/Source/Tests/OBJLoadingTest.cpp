#include "mmpch.h"
#include "Tests/OBJLoadingTest.h"

#include "Core/Entity/Transform.h"
#include "Core/Rendering/Camera.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/Shaders/StaticShader.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Utility/OBJLoader.h"

void OBJLoadingTest::OnAttach()
{
	//auto model = OBJLoader::LoadOBJ("Content/Models/Test.obj");
	auto model = OBJLoader::LoadOBJ("Content/Models/Stall.obj");
	if (!model)
	{
		MM_ERROR("OBJLoadingTest: Failed to load obj!");
		DestroySelf();
	}

	//auto texture = CreateRef<Texture>("Content/Textures/TestModelTexture.png");
	auto texture = CreateRef<Texture>("Content/Textures/StallTexture.png");
	if (texture->GetWidth() == 0)
	{
		MM_ERROR("OBJLoadingTest: Failed to load texture!");
		DestroySelf();
	}
	
	m_Camera = CreateRef<Camera>();
	m_Shader = StaticShader::Create();
	m_Entity = CreateRef<Entity>(Transform(glm::vec3(0, -2, -10)), CreateRef<TexturedModel>(model, texture));
}

void OBJLoadingTest::OnUpdate(double deltaSeconds)
{
	m_Camera->DoDefaultMovement(static_cast<float>(deltaSeconds));
	m_Entity->GetTransform().Rotation.y += static_cast<float>(deltaSeconds) * 10;
}

void OBJLoadingTest::OnRender()
{
	Renderer::Begin(m_Camera.get());
	Renderer::RenderEntity(m_Entity.get(), m_Shader.get());
	Renderer::End();
}
