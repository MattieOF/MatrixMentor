#include "mmpch.h"

#include "Core/Window.h"
#include "Core/Input/Input.h"
#include "Core/Events/Events.h"
#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Rendering/RawModel.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Rendering/Shaders/ShaderProgram.h"
#include "Core/Rendering/Shaders/StaticShader.h"

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

		std::vector<uint32_t> indices = {
			0, 1, 3, 3, 1, 2
		};

		m_Rectangle = new RawModel(verticies, indices);

		m_ShaderTest = ShaderProgram::CreateShaderProgram("Test Shader");
		m_ShaderTest->BindAttribute(0, "inPosition");
		m_ShaderTest->AddStageFromFile(GL_VERTEX_SHADER, "Content/Shaders/BasicVertex.glsl");
		m_ShaderTest->AddStageFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/BasicFragment.glsl");
		// m_ShaderTest->AddStageFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/SecondFragmentTest.glsl");
        m_ShaderTest->LinkProgram();

		m_StaticShader = CreateRef<StaticShader>();
		m_StaticShader->Bind();
	}

	void OnRender() override
	{
		Renderer::RenderModel(m_Rectangle);
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
	RawModel* m_Rectangle;

	Ref<ShaderProgram> m_ShaderTest, m_StaticShader;
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
