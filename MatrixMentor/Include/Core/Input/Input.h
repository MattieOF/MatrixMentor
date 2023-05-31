#pragma once

#include "mmpch.h"
#include "Core/Input/KeyCodes.h"
#include "Core/Input/MouseButtonCodes.h"

class Input
{
	friend class Window;

public:
	virtual ~Input() = default;

	[[nodiscard]] inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
	[[nodiscard]] inline static bool IsKeyReleased(int keyCode) { return !(s_Instance->IsKeyPressedImpl(keyCode)); }
	[[nodiscard]] inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
	[[nodiscard]] inline static bool IsMouseButtonReleased (int button) { return !(s_Instance->IsMouseButtonPressedImpl(button)); }
	[[nodiscard]] inline static std::pair<double, double> GetMousePos() { return s_Instance->GetMousePosImpl(); }
protected:
	virtual bool IsKeyPressedImpl(int keyCode) = 0;
	virtual bool IsMouseButtonPressedImpl(int button) = 0;
	virtual std::pair<double, double> GetMousePosImpl() = 0;
private:
	static Input* s_Instance;
};

class GlfwInput : public Input
{
public:
	bool IsKeyPressedImpl(int keyCode) override;
	bool IsMouseButtonPressedImpl(int button) override;
	std::pair<double, double> GetMousePosImpl() override;

	struct GLFWwindow* Window = nullptr;
};
