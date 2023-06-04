#include "mmpch.h"

#include "Core/Window.h"
#include "Core/Input/Input.h"
#include "Core/Events/Events.h"
#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Rendering/RawModel.h"
#include "Core/Rendering/Renderer.h"

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
			return false;
		});
	}

private:
	RawModel* m_Rectangle;
};

int main()
{
	InitLog();
	MM_INFO("Matrix Mentor!");

	// Initialise the window
	Window* window = nullptr;
	const WindowSpecification windowSpec = {
		"Matrix Mentor",
		1280, 600,
		true,
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
}
