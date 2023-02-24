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
    virtual EventType getEventType() const override                                                                    \
    {                                                                                                                  \
        return getStaticType();                                                                                        \
    }                                                                                                                  \
    virtual const char* getName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define EVENT_CLASS_CATEGORY(category)                                                                                 \
    virtual int getCategoryFlags() const override                                                                      \
    {                                                                                                                  \
        return category;                                                                                               \
    }


    class MINT_API Event
    {
        friend class EventDispatcher;
        friend class EventBus;

      public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const    = 0;
        virtual int getCategoryFlags() const   = 0;
        virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category) const { return getCategoryFlags() & category; }
        inline bool handled() const { return m_handled; }

      protected:
        bool m_handled = false;
    };

    class EventDispatcher
    {
        // The event callback function
        template <typename T>
        using EventFn = std::function<bool(T&)>;

      public:
        EventDispatcher(Event& event) : m_event(event) {}

        template <typename T>
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

    /*
    class EventListener
    {
        using EventFn = std::function<bool(Event&)>;

      public:
        EventListener(EventFn func) : m_callbackFn(func) {}

        bool handleEvent(Event& e) { return m_callbackFn(e); }

      private:
        EventFn m_callbackFn;
    };


    class EventBus
    {
      public:
        EventBus(){};
        ~EventBus(){};


        static void onUpdate()
        {

            while (!m_eventBus.empty())
            {
                // Get the next event (local now owns the on-heap event object)
                std::unique_ptr<Event> local(std::move(m_eventBus.front()));
                m_eventBus.pop();

                EventType eType = local->getEventType();

                auto it = m_routingTable.find(eType);
                if (it != m_routingTable.end())
                {
                    for (auto listener : ((*it).second)) { local->m_handled = listener->handleEvent(*local); }
                }
            }
        }


        static void postEvent(std::unique_ptr<Event> e)
        {
            // The EventBus now owns the object pointed to by e
            m_eventBus.push(std::unique_ptr<Event>(std::move(e)));
        }


        static void registerListener(EventType eType, EventListener* listener)
        {
            // Add this listener entry
            // If the routing table doesn't have an entry for t, std::map.operator[] will add one
            // If the listener is alredy registered std::set.insert() won't do anything
            m_routingTable[eType].insert(listener);
        }


        static void removeListener(EventType eType, EventListener* listener)
        {
            // Check if an entry for the event type exists
            auto keyIterator = m_routingTable.find(eType);
            if (keyIterator != m_routingTable.end())
            {
                // Remove the given callback if it exists in the set
                m_routingTable[eType].erase(listener);
            }
        }


      private:
        static std::queue<std::unique_ptr<Event>> m_eventBus;
        static std::map<EventType, std::set<EventListener*>> m_routingTable;
    };
    */

} // namespace mint
