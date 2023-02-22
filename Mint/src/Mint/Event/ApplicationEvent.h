#pragma once

#include "Event.h"

#include <sstream>

namespace mint
{
    class MINT_API WindowResizeEvent : public Event
    {
      public:
        WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

        inline unsigned int getWidth() const { return m_width; }
        inline unsigned int getHeight() const { return m_height; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_width << ", " << m_height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

      private:
        unsigned int m_width, m_height;
    };

    class MINT_API WindowCloseEvent : public Event
    {
      public:
        WindowCloseEvent() {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowCloseEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MINT_API WindowMovedEvent : public Event
    {
      public:
        WindowMovedEvent(int x, int y) : m_windowX(x), m_windowY(y) {}

        inline unsigned int getX() const { return m_windowX; }
        inline unsigned int getY() const { return m_windowY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowMovedEvent: " << m_windowX << ", " << m_windowY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

      private:
        int m_windowX, m_windowY;
    };

    class MINT_API WindowFocusEvent : public Event
    {
      public:
        WindowFocusEvent() {}

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MINT_API WindowLostFocusEvent : public Event
    {
      public:
        WindowLostFocusEvent() {}

        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MINT_API AppTickEvent : public Event
    {
      public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MINT_API AppUpdateEvent : public Event
    {
      public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class MINT_API AppRenderEvent : public Event
    {
      public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

} // namespace mint
