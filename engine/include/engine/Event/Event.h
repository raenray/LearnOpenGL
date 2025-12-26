#pragma once

namespace Engine
{

enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

enum EventCategory
{
    None                     = 0,
    EventCategoryApplication = 1 << 0,
    EventCategoryInput       = 1 << 1,
    EventCategoryKeyboard    = 1 << 2,
    EventCategoryMouse       = 1 << 3,
    EventCategoryMouseButton = 1 << 4
};

class Event
{
public:
    bool m_handled = false;

    virtual EventType   getEventType() const     = 0;
    virtual const char* getName() const          = 0;
    virtual int         getCategoryFlags() const = 0;

    bool isInCategory(EventCategory category) { return getCategoryFlags() & category; }
};

class EventDispatcher
{
public:
    EventDispatcher(Event& event)
        : m_event(event)
    {
    }

    template <typename T, typename F> bool dispatch(const F& func)
    {
        if (m_event.getEventType() == T::getStaticType())
        {
            m_event.m_handled = func(static_cast<T&>(m_event));

            return m_event.m_handled;
        }
        return false;
    }

private:
    Event& m_event;
};

} // namespace Engine
