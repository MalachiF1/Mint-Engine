#pragma once
#include "mtpch.h"

#include "Mint/Core/Base.h"
#include "Mint/Event/Event.h"

namespace mint
{

struct WindowProps
{
    std::string title;
    uint32_t    width;
    uint32_t    height;

    WindowProps(const std::string& title = "Mint Engine", uint32_t width = 1280, uint32_t height = 720) :
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

    virtual uint32_t getWidth() const  = 0;
    virtual uint32_t getHeight() const = 0;

    virtual std::pair<uint32_t, uint32_t> getSize() const = 0;

    virtual void setEventCallback(const EventCallbackFn& callback) = 0;
    virtual void setVSync(bool enabled)                            = 0;
    virtual bool isVSync() const                                   = 0;

    // Will return a pointer to the window object per implementation (eg. GLFWwindow*)
    virtual void* getNativeWindow() const = 0;

    // To be implemented per platform
    static Scope<Window> create(const WindowProps& props = WindowProps());
};

} // namespace mint
