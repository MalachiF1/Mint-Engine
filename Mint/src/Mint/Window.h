#pragma once
#include "mtpch.h"

#include "Mint/Core.h"
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

    // This window class is an interface for the desktop platform-dependant window class (e.g WindowsWindow).
    // We will call this window class in the window api, but the implementation will be per platform.
    class MINT_API Window
    {
      public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window(){};

        virtual void onUpdate() = 0;

        virtual unsigned int getWidth() const           = 0;
        virtual unsigned int getHeight() const          = 0;
        virtual std::pair<float, float> getSize() const = 0;

        // Window attributes
        virtual void setEventCallback(const EventCallbackFn& callback) = 0;
        virtual void setVSync(bool enabled)                            = 0;
        virtual bool isVSync() const                                   = 0;

        // Will return a pointer to the window object per implementation (eg. GLFWwindow*)
        virtual void* getNativeWindow() const = 0;

        // To be implemented per platform
        static Window* create(const WindowProps& props = WindowProps());
    };

} // namespace mint
