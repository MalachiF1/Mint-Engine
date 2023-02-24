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

        inline unsigned int getWidth() const override { return m_data.width; }
        inline unsigned int getHeight() const override { return m_data.width; }
        inline std::pair<float, float> getSize() const override { return std::pair<float, float>(m_data.width, m_data.height); }

        // Window attributes
        inline void setEventCallback(const EventCallbackFn& callback) override { m_data.eventCallback = callback; }
        void setVSync(bool enabled) override;
        inline bool isVSync() const override { return m_data.VSync; };

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
