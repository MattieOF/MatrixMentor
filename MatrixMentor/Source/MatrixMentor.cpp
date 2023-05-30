#include "mmpch.h"

#include "Core/Window.h"

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
		true
	};
	if (!Window::Create(windowSpec, window))
		return -1;

	window->Run();

	// Clean up
	delete window;
}
