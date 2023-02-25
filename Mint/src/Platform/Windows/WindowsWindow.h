#pragma once

#include "Mint/Window.h"

#include <GLFW/glfw3.h>

namespace mint
{

    class WindowsWindow : public Window
    {
      public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void onUpdate() override;

        inline virtual unsigned int getWidth() const override { return m_data.width; }
        inline virtual unsigned int getHeight() const override { return m_data.width; }
        inline virtual std::pair<float, float> getSize() const override
        {
            return std::pair<float, float>(m_data.width, m_data.height);
        }

        // Window attributes
        inline virtual void setEventCallback(const EventCallbackFn& callback) override
        {
            m_data.eventCallback = callback;
        }
        virtual void setVSync(bool enabled) override;
        inline virtual bool isVSync() const override { return m_data.VSync; };

        inline virtual void* getNativeWindow() const override { return m_window; }

      private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

      private:
        GLFWwindow* m_window;

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
