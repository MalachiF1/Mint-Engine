#pragma once
#include "mtpch.h"

#include "Mint/Core/Base.h"
#include "Mint/Event/Event.h"

namespace mint
{
    struct WindowProps
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title = "Mint Engine", unsigned int width = 1280, unsigned int height = 720) :
            title(title), width(width), height(height)
        {
        }
    };

    class Window
    {
      public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void onUpdate() = 0;

        virtual unsigned int getWidth() const                         = 0;
        virtual unsigned int getHeight() const                        = 0;
        virtual std::pair<unsigned int, unsigned int> getSize() const = 0;

        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enabled)                            = 0;
        virtual bool isVSync() const                                   = 0;

        // Will return a pointer to the window object per implementation (eg. GLFWwindow*)
        virtual void* getNativeWindow() const = 0;

        // To be implemented per platform
        static Scope<Window> create(const WindowProps& props = WindowProps());
    };

} // namespace mint
