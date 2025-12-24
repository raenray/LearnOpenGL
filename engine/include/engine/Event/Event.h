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
    bool Handled = false;

    virtual EventType   GetEventType() const     = 0;
    virtual const char* GetName() const          = 0;
    virtual int         GetCategoryFlags() const = 0;

    bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
};

} // namespace Engine
