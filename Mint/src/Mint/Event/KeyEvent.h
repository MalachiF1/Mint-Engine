#pragma once
#include "mtpch.h"

#include "Event.h"

namespace mint
{

    // Parent of key-press and key-release events.
    // The keycode is the same for both. KeyReleaseEvent doesn't need a repeat count.
    class MINT_API KeyEvent : public Event
    {
      public:
        inline int getKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

      protected:
        KeyEvent(int keycode) : m_keyCode(keycode) {}

        int m_keyCode;
    };

    class MINT_API KeyPressedEvent : public KeyEvent
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

    class MINT_API KeyReleasedEvent : public KeyEvent
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

} // namespace mint