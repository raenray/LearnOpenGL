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

    float GetX() const { return m_MouseX; }
    float GetY() const { return m_MouseY; }

    static EventType    GetStaticType() { return EventType::MouseMoved; }
    virtual EventType   GetEventType() const override { return GetStaticType(); }
    virtual const char* GetName() const override { return "MouseMoved"; }

    virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }

private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(const float xOffset, const float yOffset)
        : m_XOffset(xOffset)
        , m_YOffset(yOffset)
    {
    }
    float GetXOffset() const { return m_XOffset; }
    float GetYOffset() const { return m_YOffset; }

    static EventType    GetStaticType() { return EventType::MouseScrolled; }
    virtual EventType   GetEventType() const override { return GetStaticType(); }
    virtual const char* GetName() const override { return "MouseScrolled"; }

    virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse; }

private:
    float m_XOffset, m_YOffset;
};

class MouseButtonPressedEvent : public Event
{
public:
    MouseButtonPressedEvent(const int button)
        : m_Button(button)
    {
    }

    int GetMouseButton() const { return m_Button; }

    static EventType    GetStaticType() { return EventType::MouseButtonPressed; }
    virtual EventType   GetEventType() const override { return GetStaticType(); }
    virtual const char* GetName() const override { return "MouseButtonPressed"; }

    virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }

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

    int GetMouseButton() const { return m_Button; }

    static EventType    GetStaticType() { return EventType::MouseButtonReleased; }
    virtual EventType   GetEventType() const override { return GetStaticType(); }
    virtual const char* GetName() const override { return "MouseButtonReleased"; }

    virtual int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton; }

private:
    int m_Button;
};

} // namespace Engine
