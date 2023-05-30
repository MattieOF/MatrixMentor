#include "mmpch.h"

#include "Core/Window.h"
#include "Core/Rendering/BaseOpenGLLayer.h"

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
		GLSettings()
	};
	if (!Window::Create(windowSpec, window))
		return -1;

	window->PushLayer(new BaseOpenGLLayer());

	window->Run();

	// Clean up
	delete window;
}
