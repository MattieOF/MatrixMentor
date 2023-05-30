#include "MMpch.h"

#include "Core/Input/Input.h"

#include "GLFW/glfw3.h"

Input* Input::s_Instance = nullptr;

bool GlfwInput::IsKeyPressedImpl(int keyCode)
{
	return glfwGetKey(Window, keyCode) == GLFW_PRESS;
}

bool GlfwInput::IsMouseButtonPressedImpl(int button)
{
	return glfwGetMouseButton(Window, button) == GLFW_PRESS;
}

std::pair<double, double> GlfwInput::GetMousePosImpl()
{
	std::pair<double, double> pos; 
	glfwGetCursorPos(Window, &pos.first, &pos.second);
	return pos;
}
