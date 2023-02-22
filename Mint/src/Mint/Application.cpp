#include "mtpch.h"

#include "Application.h"

#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/Event.h"

#include <GLFW/glfw3.h>

namespace mint
{

    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application() {}


    void Application::run()
    {
        while (m_running)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->onUpdate();
        }
    }

} // namespace mint
