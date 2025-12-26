#pragma once

#include <engine\Event\Event.h>

#include <string>
#include <sstream>

namespace Engine
{

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_width(width)
        , m_height(height)
    {
    }

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    static EventType    getStaticType() { return EventType::WindowResize; }
    virtual EventType   getEventType() const override { return getStaticType(); }
    virtual const char* getName() const override { return "WindowResize"; }

    virtual int getCategoryFlags() const override { return EventCategoryApplication; }

private:
    unsigned int m_width, m_height;
};

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

    static EventType    getStaticType() { return EventType::WindowClose; }
    virtual EventType   getEventType() const override { return getStaticType(); }
    virtual const char* getName() const override { return "WindowClose"; }

    virtual int getCategoryFlags() const override { return EventCategoryApplication; }
};

} // namespace Engine
