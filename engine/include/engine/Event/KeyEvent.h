#pragma once

#include <engine\Event\Event.h>

namespace Engine
{

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent(int keyCode, bool repeat = false)
        : m_KeyCode(keyCode)
        , m_Repeat(repeat)
    {
    }

    int  GetKeyCode() const { return m_KeyCode; }
    bool IsRepeat() const { return m_Repeat; }

    static EventType GetStaticType() { return EventType::KeyReleased; }
    EventType        GetEventType() const override { return EventType::KeyPressed; }
    const char*      GetName() const override { return "KeyPressed"; }
    int              GetCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; }

private:
    int  m_KeyCode;
    bool m_Repeat;
};

class KeyReleasedEvent : public Event
{
public:
    KeyReleasedEvent(int keyCode, bool repeat = false)
        : m_KeyCode(keyCode)
        , m_Repeat(repeat)
    {
    }

    int  GetKeyCode() const { return m_KeyCode; }
    bool IsRepeat() const { return m_Repeat; }

    static EventType GetStaticType() { return EventType::KeyReleased; }
    EventType        GetEventType() const override { return EventType::KeyReleased; }
    const char*      GetName() const override { return "KeyReleased"; }

    int GetCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; }

private:
    int  m_KeyCode;
    bool m_Repeat;
};

} // namespace Engine
