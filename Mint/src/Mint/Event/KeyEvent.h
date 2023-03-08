#pragma once
#include "mtpch.h"

#include "Event.h"

namespace mint
{

// Parent of key-press and key-release events.
// The keycode is the same for both. KeyReleaseEvent doesn't need a repeat count.
class KeyEvent : public Event
{
  public:
    inline int getKeyCode() const { return m_keyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

  protected:
    KeyEvent(int keycode) : m_keyCode(keycode) {}

    int m_keyCode;
};

class KeyPressedEvent final : public KeyEvent
{
  public:
    KeyPressedEvent(int keycode, int repeateCount) : KeyEvent(keycode), m_repeatCount(repeateCount) {}

    inline int getRepeatCount() const { return m_repeatCount; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeates)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

  private:
    int m_repeatCount;
};

class KeyReleasedEvent final : public KeyEvent
{
  public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_keyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent final : public KeyEvent
{
  public:
    KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_keyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};

} // namespace mint
