#include "mmpch.h"

#include <GLFW/glfw3.h>

int main()
{
	InitLog();
	MM_INFO("Matrix Mentor!");

	if (!glfwInit())
	{
		const char* error;
		glfwGetError(&error);
		MM_ERROR("Failed to initialise GLFW! Error: {0}", error);
		return -1;
	}
	else
	{
		const char* version = glfwGetVersionString();
		MM_INFO("Successfully initialised GLFW ({0})", version);
	}

	std::cin.get();
}
