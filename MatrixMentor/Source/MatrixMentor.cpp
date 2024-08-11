#include "mmpch.h"

#include "Core/Window.h"
#include "Core/Input/Input.h"
#include "Core/Events/Events.h"
#include "Core/Rendering/BaseOpenGLLayer.h"
#include "Core/Utility/DebugInfoLayer.h"
#include "Tests/TestSelectionLayer.h"

bool s_ShouldRestart = false;

int main()
{
	InitLog();
	MM_INFO("Matrix Mentor!");

	do
	{
		// Initialise the window
		Window*                   window     = nullptr;
		const WindowSpecification windowSpec = {
			"Matrix Mentor",
			1280, 600,
			false,
			true,
			true,
			GLSettings{4, 6}
		};
		if (!Window::Create(windowSpec, window))
			return -1;

		window->PushLayer(new BaseOpenGLLayer());
		window->PushLayer(new DebugInfoLayer());
		window->PushLayer(new TestSelectionLayer());

		window->Run();

		// Clean up
		delete window;
	}
	while (s_ShouldRestart);
}
