#pragma once

#include "Mint/Core/Window.h"
#include "Mint/Renderer/RenderingContext.h"

#include <GLFW/glfw3.h>

namespace mint
{

class WindowsWindow final : public Window
{
  public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void onUpdate() override;

    inline virtual uint32_t getWidth() const override { return m_data.width; }
    inline virtual uint32_t getHeight() const override { return m_data.width; }

    inline virtual std::pair<uint32_t, uint32_t> getSize() const override
    {
        return std::pair<uint32_t, uint32_t>(m_data.width, m_data.height);
    }

    // Window attributes
    inline virtual void setEventCallback(const EventCallbackFn& callback) override { m_data.eventCallback = callback; }
    virtual void        setVSync(bool enabled) override;
    inline virtual bool isVSync() const override { return m_data.VSync; };

    inline virtual void* getNativeWindow() const override { return m_window; }

  private:
    virtual void init(const WindowProps& props);
    virtual void shutdown();

  private:
    GLFWwindow* m_window;

    RenderingContext* m_context;

    struct WindowData
    {
        std::string title;
        uint32_t    width, height;
        bool        VSync;

        EventCallbackFn eventCallback;
    };

    WindowData m_data;
};

} // namespace mint
