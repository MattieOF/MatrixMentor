#pragma once

#include "mmpch.h"

#include <bitset>

#include "Core/Input/KeyCodes.h"
#include "Core/Input/MouseButtonCodes.h"

class Input
{
	friend class Window;

public:
	virtual ~Input() = default;

	[[nodiscard]] static bool IsKeyDown(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }

	[[nodiscard]] static bool IsKeyJustDown(int keyCode)
	{
		return m_KeysDownNow[keyCode] && !m_KeysDownLastFrame[keyCode];
	}

	[[nodiscard]] static bool IsKeyReleased(int keyCode) { return !(s_Instance->IsKeyPressedImpl(keyCode)); }
	[[nodiscard]] static bool IsKeyJustReleased(int keyCode) { return !(s_Instance->IsKeyPressedImpl(keyCode)); }
	[[nodiscard]] static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

	[[nodiscard]] static bool IsMouseButtonReleased(int button)
	{
		return !(s_Instance->IsMouseButtonPressedImpl(button));
	}

	[[nodiscard]] static std::pair<double, double> GetMousePos() { return s_Instance->GetMousePosImpl(); }

	static void UpdateInput()
	{
		m_KeysDownLastFrame         = m_KeysDownNow;
		m_MouseButtonsDownLastFrame = m_MouseButtonsDownNow;
	}

protected:
	virtual bool                      IsKeyPressedImpl(int keyCode) = 0;
	virtual bool                      IsMouseButtonPressedImpl(int button) = 0;
	virtual std::pair<double, double> GetMousePosImpl() = 0;

	static std::bitset<MM_KEY_LAST + 1>          m_KeysDownNow,         m_KeysDownLastFrame;
	static std::bitset<MM_MOUSE_BUTTON_LAST + 1> m_MouseButtonsDownNow, m_MouseButtonsDownLastFrame;

private:
	static Input* s_Instance;
};

class GlfwInput : public Input
{
public:
	bool                      IsKeyPressedImpl(int keyCode) override;
	bool                      IsMouseButtonPressedImpl(int button) override;
	std::pair<double, double> GetMousePosImpl() override;

	struct GLFWwindow* Window = nullptr;
};
