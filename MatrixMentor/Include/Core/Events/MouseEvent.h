#pragma once

#include "Core/Events/Event.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y)
		: m_MouseX(x), m_MouseY(y)
	{}

	EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
	EVENT_CLASS_TYPE(MouseMoved)

	[[nodiscard]] inline float GetX() const { return m_MouseX; }
	[[nodiscard]] inline float GetY() const { return m_MouseY; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

private:
	float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(double xOffset, double yOffset)
		: m_XOffset(xOffset), m_YOffset(yOffset)
	{}

	EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
	EVENT_CLASS_TYPE(MouseScrolled)

	[[nodiscard]] inline double GetXOffset() const { return m_XOffset; }
	[[nodiscard]] inline double GetYOffset() const { return m_YOffset; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_XOffset << ", " << m_YOffset;
		return ss.str();
	}

private:
	double m_XOffset, m_YOffset;
};

class MouseButtonPressedEvent : public Event
{
public:
	MouseButtonPressedEvent(int button)
		: m_Button(button)
	{}

	EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
	EVENT_CLASS_TYPE(MouseButtonPressed)

	[[nodiscard]] inline int GetButton() const { return m_Button; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

private:
	int m_Button;
};

class MouseButtonReleasedEvent : public Event
{
public:
	MouseButtonReleasedEvent(int button)
		: m_Button(button)
	{}

	EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
	EVENT_CLASS_TYPE(MouseButtonReleased)

	[[nodiscard]] inline int GetButton() const { return m_Button; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}

private:
	int m_Button;
};
