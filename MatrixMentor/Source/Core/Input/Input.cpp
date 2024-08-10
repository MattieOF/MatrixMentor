#include "MMpch.h"

#include "Core/Input/Input.h"

#include "imgui.h"
#include "GLFW/glfw3.h"

Input* Input::s_Instance = nullptr;

std::bitset<MM_KEY_LAST + 1>          Input::m_KeysDownNow, Input::m_KeysDownLastFrame;
std::bitset<MM_MOUSE_BUTTON_LAST + 1> Input::m_MouseButtonsDownNow, Input::m_MouseButtonsDownLastFrame;

bool GlfwInput::IsKeyPressedImpl(int keyCode)
{
	return !ImGui::GetIO().WantCaptureKeyboard && glfwGetKey(Window, keyCode) == GLFW_PRESS;
}

bool GlfwInput::IsMouseButtonPressedImpl(int button)
{
	return !ImGui::GetIO().WantCaptureMouse && glfwGetMouseButton(Window, button) == GLFW_PRESS;
}

std::pair<double, double> GlfwInput::GetMousePosImpl()
{
	std::pair<double, double> pos; 
	glfwGetCursorPos(Window, &pos.first, &pos.second);
	return pos;
}
