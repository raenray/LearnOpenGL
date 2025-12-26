#pragma once

#include <engine\Event\Event.h>

namespace Engine
{

class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(const float x, const float y)
        : m_MouseX(x)
        , m_MouseY(y)
    {
    }

    float getX() const { return m_MouseX; }
    float getY() const { return m_MouseY; }

    static EventType    getStaticType() { return EventType::MouseMoved; }
    virtual EventType   getEventType() const override { return getStaticType(); }
    virtual const char* getName() const override { return "MouseMoved"; }

    virtual int getCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }

private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(const float xOffset, const float yOffset)
        : m_xOffset(xOffset)
        , m_yOffset(yOffset)
    {
    }
    float getXOffset() const { return m_xOffset; }
    float getYOffset() const { return m_yOffset; }

    static EventType    getStaticType() { return EventType::MouseScrolled; }
    virtual EventType   getEventType() const override { return getStaticType(); }
    virtual const char* getName() const override { return "MouseScrolled"; }

    virtual int getCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }

private:
    float m_xOffset, m_yOffset;
};

class MouseButtonPressedEvent : public Event
{
public:
    MouseButtonPressedEvent(const int button)
        : m_Button(button)
    {
    }

    int getMouseButton() const { return m_Button; }

    static EventType    getStaticType() { return EventType::MouseButtonPressed; }
    virtual EventType   getEventType() const override { return getStaticType(); }
    virtual const char* getName() const override { return "MouseButtonPressed"; }

    virtual int getCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }

private:
    int m_Button;
};

class MouseButtonReleasedEvent : public Event
{
public:
    MouseButtonReleasedEvent(const int button)
        : m_Button(button)
    {
    }

    int getMouseButton() const { return m_Button; }

    static EventType    getStaticType() { return EventType::MouseButtonReleased; }
    virtual EventType   getEventType() const override { return getStaticType(); }
    virtual const char* getName() const override { return "MouseButtonReleased"; }

    virtual int getCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }

private:
    int m_Button;
};

} // namespace Engine
