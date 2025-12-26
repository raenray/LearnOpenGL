#pragma once

#include <engine\Event\Event.h>

namespace Engine
{

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent(int keyCode, bool repeat = false)
        : m_keyCode(keyCode)
        , m_repeat(repeat)
    {
    }

    int  GetKeyCode() const { return m_keyCode; }
    bool IsRepeat() const { return m_repeat; }

    static EventType getStaticType() { return EventType::KeyPressed; }
    EventType        getEventType() const override { return EventType::KeyPressed; }
    const char*      getName() const override { return "KeyPressed"; }

    int getCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; }

private:
    int  m_keyCode;
    bool m_repeat;
};

class KeyReleasedEvent : public Event
{
public:
    KeyReleasedEvent(int keyCode, bool repeat = false)
        : m_keyCode(keyCode)
        , m_repeat(repeat)
    {
    }

    int  getKeyCode() const { return m_keyCode; }
    bool isRepeat() const { return m_repeat; }

    static EventType getStaticType() { return EventType::KeyReleased; }
    EventType        getEventType() const override { return EventType::KeyReleased; }
    const char*      getName() const override { return "KeyReleased"; }

    int getCategoryFlags() const override { return EventCategoryInput | EventCategoryKeyboard; }

private:
    int  m_keyCode;
    bool m_repeat;
};

} // namespace Engine
