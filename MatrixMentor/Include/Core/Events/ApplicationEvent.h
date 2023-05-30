#pragma once

#include "Core/Events/Event.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{}

	EVENT_CLASS_CATEGORY(EC_Application)
	EVENT_CLASS_TYPE(WindowResize)

	[[nodiscard]] FORCEINLINE uint32_t GetWidth()  const { return m_Width;  }
	[[nodiscard]] FORCEINLINE uint32_t GetHeight() const { return m_Height; }

	[[nodiscard]] std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}
private:
	uint32_t m_Width, m_Height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_CATEGORY(EC_Application)
	EVENT_CLASS_TYPE(WindowClose)
};

class AppTickEvent : public Event
{
public:
	AppTickEvent() = default;

	EVENT_CLASS_CATEGORY(EC_Application)
	EVENT_CLASS_TYPE(AppTick)
};

class AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() = default;

	EVENT_CLASS_CATEGORY(EC_Application)
	EVENT_CLASS_TYPE(AppUpdate)
};

class AppRenderEvent : public Event
{
public:
	AppRenderEvent() = default;

	EVENT_CLASS_CATEGORY(EC_Application)
	EVENT_CLASS_TYPE(AppRender)
};
