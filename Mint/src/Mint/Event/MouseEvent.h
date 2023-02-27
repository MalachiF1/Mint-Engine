#pragma once
#include "mtpch.h"

#include "Event.h"

namespace mint
{

    // Parent of key-press and key-release events.
    // The keycode is the same for both. KeyReleaseEvent doesn't need a repeat count.
    class MouseMovedEvent : public Event
    {
      public:
        MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

        inline float getX() const { return m_mouseX; }
        inline float getY() const { return m_mouseY; }

        std::string toString() const override final
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

      private:
        float m_mouseX, m_mouseY;
    };

    class MouseScrolledEvent : public Event
    {
      public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

        inline float getXOffset() const { return m_xOffset; }
        inline float getYOffset() const { return m_yOffset; }

        std::string toString() const override final
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

      private:
        float m_xOffset, m_yOffset;
    };

    // Parent of MouseButtonPressed and MouseButtonReleased
    class MouseButtonEvent : public Event
    {
      public:
        inline int getMouseButton() const { return m_button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

      protected:
        MouseButtonEvent(int button) : m_button(button) {}
        int m_button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        std::string toString() const override final
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << getMouseButton();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
      public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string toString() const override final
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << getMouseButton();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

} // namespace mint
