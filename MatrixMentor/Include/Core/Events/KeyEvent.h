#pragma once

#include "Core/Events/Event.h"

class KeyPressedEvent : public Event
{
public:
	KeyPressedEvent(int keycode, bool repeat)
		: m_KeyCode(keycode), m_Repeat(repeat)
	{ }

	EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)
	EVENT_CLASS_TYPE(KeyPressed)

	[[nodiscard]] inline int GetKeyCode() const { return m_KeyCode; }
	[[nodiscard]] inline bool IsRepeat() const { return m_Repeat; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << (m_Repeat ? "" : " not ") << "repeating)";
		return ss.str();
	}

protected:
	int m_KeyCode;
	bool m_Repeat;
};

class KeyReleasedEvent : public Event
{
public:
	KeyReleasedEvent(int keycode)
		: m_KeyCode(keycode)
	{ }

	EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)
	EVENT_CLASS_TYPE(KeyReleased)

	[[nodiscard]] inline int GetKeyCode() const { return m_KeyCode; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

protected:
	int m_KeyCode;
};

class KeyTypedEvent : public Event
{
public:
	KeyTypedEvent(int keycode)
		: m_KeyCode(keycode)
	{ }

	EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)
	EVENT_CLASS_TYPE(KeyTyped)

	[[nodiscard]] inline int GetKeyCode() const { return m_KeyCode; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}

protected:
	int m_KeyCode;
};

