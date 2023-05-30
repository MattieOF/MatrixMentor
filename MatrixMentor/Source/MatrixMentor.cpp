#include "mmpch.h"

#include "Core/Window.h"
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
			0.5f, -0.5f, 0.f,
			0.5f, 0.5f, 0.f,
			-0.5f, 0.5f, 0.f
		};
		m_Rectangle = new RawModel(verticies);
	}

	void OnRender() override
	{
		Renderer::RenderModel(m_Rectangle);
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
