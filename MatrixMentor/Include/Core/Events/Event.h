#pragma once

#include "MatrixMentor.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

enum EventCategory
{
	None            = 0,
	EC_Application  = BIT(0),
	EC_Input        = BIT(1),
	EC_Keyboard     = BIT(2),
	EC_Mouse        = BIT(3),
	EC_MouseButton  = BIT(4)
};

class Event
{
	friend class EventDispatcher;

public:
	[[nodiscard]] virtual EventType GetEventType() const = 0;
	[[nodiscard]] virtual const char* GetName() const = 0;
	[[nodiscard]] virtual int GetCategoryFlags() const = 0;
	[[nodiscard]] virtual std::string ToString() const { return GetName(); }

	[[nodiscard]] inline bool IsInCategory(const EventCategory category) const
	{
		return GetCategoryFlags() & category;
	}

	bool Handled = false;
};

class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event)
		: m_Event(event)
	{
	}

	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.Handled = func(*static_cast<T*>(&m_Event));
			return true;
		}

		return false;
	}
private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}
