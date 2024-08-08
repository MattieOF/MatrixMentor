#include "mmpch.h"

#include "Core/Window.h"
#include "Core/Input/Input.h"
#include "Core/Events/Events.h"
#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/Shaders/StaticShader.h"
#include "Core/Rendering/TexturedModel.h"
#include "Core/Entity/Entity.h"

class QuadTestLayer : public Layer
{
public:
	QuadTestLayer()
	{
		std::vector<float> verticies = {
			-0.5f, 0.5f, 0.f,
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.5f, 0.5f, 0.f,
		};

        std::vector<float> texCoords = {
                0, 0,
                0, 1,
                1, 1,
                1, 0,
        };

		std::vector<uint32_t> indices = {
			0, 1, 3, 3, 1, 2,
		};

		auto rectangleMesh = CreateRef<RawModel>(verticies, texCoords, indices);
        auto testTexture = CreateRef<Texture>("Content/Textures/PUPPY.jpg");
        auto texturedModel = CreateRef<TexturedModel>(rectangleMesh, testTexture);
		m_TestEntity = CreateRef<Entity>(texturedModel);

		m_StaticShader = CreateRef<StaticShader>();
		m_StaticShader->Bind();
	}

	void OnRender() override
	{
		Renderer::RenderEntity(m_TestEntity.get(), m_StaticShader.get());
	}

	void OnUpdate(double deltaSeconds) override
	{
		m_TestEntity->GetTransform().Scale += static_cast<float>(deltaSeconds) / 10;
		if (Input::IsKeyJustDown(MM_KEY_S))
			m_TestEntity->GetTransform().Scale += 0.2f;

		if (Input::IsKeyDown(MM_KEY_A))
			m_TestEntity->GetTransform().Rotation.z += static_cast<float>(deltaSeconds) * 10;
		if (Input::IsKeyDown(MM_KEY_D))
			m_TestEntity->GetTransform().Rotation.z -= static_cast<float>(deltaSeconds) * 10;
	}
	
	void OnEvent(Event& event) override
	{
		EventDispatcher dispatcher(event);
		
		dispatcher.Dispatch<KeyPressedEvent>([this](const KeyPressedEvent& keyPressedEvent)
		{
			if (keyPressedEvent.GetKeyCode() == MM_KEY_ESCAPE)
				m_Window->Close();
			else if (keyPressedEvent.GetKeyCode() == MM_KEY_R
				&& !keyPressedEvent.IsRepeat())
			{
				s_ShouldRestart = !s_ShouldRestart;
				if (s_ShouldRestart)
					MM_INFO("The application will now restart on quit.");
				else
					MM_INFO("The application will now shutdown fully on quit.");
			}
			return false;
		});
	}

private:
	Ref<StaticShader> m_StaticShader;
	Ref<Entity> m_TestEntity;
};

int main()
{
	InitLog();
	MM_INFO("Matrix Mentor!");

	do
	{
		// Initialise the window
		Window* window = nullptr;
		const WindowSpecification windowSpec = {
			"Matrix Mentor",
			1280, 600,
			false,
			true,
			true,
			GLSettings {4, 6}
		};
		if (!Window::Create(windowSpec, window))
			return -1;

		window->PushLayer(new BaseOpenGLLayer());
		window->PushLayer(new QuadTestLayer());

		window->Run();

		// Clean up
		delete window;
	} while (s_ShouldRestart);
}
