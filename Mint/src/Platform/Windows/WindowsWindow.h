#pragma once

#include "Mint/Core/Window.h"
#include "Mint/Renderer/RenderingContext.h"

#include <GLFW/glfw3.h>

namespace mint
{

    class WindowsWindow : public Window
    {
      public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow() final;

        void onUpdate() override;

        inline virtual unsigned int getWidth() const override final { return m_data.width; }
        inline virtual unsigned int getHeight() const override final { return m_data.width; }
        inline virtual std::pair<unsigned int, unsigned int> getSize() const override final
        {
            return std::pair<unsigned int, unsigned int>(m_data.width, m_data.height);
        }

        // Window attributes
        inline virtual void setEventCallback(const EventCallbackFn& callback) override final
        {
            m_data.eventCallback = callback;
        }
        virtual void setVSync(bool enabled) override final;
        inline virtual bool isVSync() const override final { return m_data.VSync; };

        inline virtual void* getNativeWindow() const override final { return m_window; }

      private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

      private:
        GLFWwindow* m_window;

        RenderingContext* m_context;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool VSync;

            EventCallbackFn eventCallback;
        };

        WindowData m_data;
    };

} // namespace mint
