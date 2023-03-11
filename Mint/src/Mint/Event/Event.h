#pragma once
#include "mtpch.h"

namespace mint
{

// Events are currently blocking.
// TODO: create an event queue and proccess events during the "event" part of the update loop.

enum class EventType
{
    None = 0,

    // Application events
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,

    // Keyboard events
    KeyTyped,
    KeyPressed,
    KeyReleased,

    // Mouse events
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

enum EventCategory
{
    None                     = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4),
};

#define EVENT_CLASS_TYPE(type)                                                                                         \
    static EventType getStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::##type;                                                                                      \
    }                                                                                                                  \
    virtual EventType getEventType() const override final                                                              \
    {                                                                                                                  \
        return getStaticType();                                                                                        \
    }                                                                                                                  \
    virtual const char* getName() const override final                                                                 \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    virtual int getCategoryFlags() const override final                                                                \
    {                                                                                                                  \
        return category;                                                                                               \
    }


class Event
{
    friend class EventDispatcher;
    friend class EventBus;

  public:
    virtual ~Event() = default;

    virtual EventType getEventType() const = 0;
    virtual const char* getName() const    = 0;
    virtual int getCategoryFlags() const   = 0;
    virtual std::string toString() const { return getName(); }

    inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }
    inline bool isHandled() const { return m_handled; }
    inline void setHandled(bool handled) { m_handled = handled; }

  protected:
    bool m_handled = false;
};

class EventDispatcher
{
    // The event callback function
    template<typename T>
    using EventFn = std::function<bool(T&)>;

  public:
    EventDispatcher(Event& event) : m_event(event) {}

    template<typename T>
    bool dispatch(EventFn<T> func)
    {
        if (m_event.getEventType() == T::getStaticType())
        {
            m_event.m_handled = func(*(T*)&m_event);
            return true;
        }
        return false;
    }

  private:
    Event& m_event;
};


inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.toString();
}

} // namespace mint
