#include "mtpch.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace mint
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application()
    {
        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
    }

    Application::~Application() {}


    void Application::pushLayer(Layer* layer)
    {
        m_layerStack.pushLayer(layer);
    }

    void Application::popLayer(Layer* layer)
    {
        m_layerStack.popLayer(layer);
    }

    void Application::pushOverLay(Layer* overlay)
    {
        m_layerStack.pushOverlay(overlay);
    }

    void Application::popOverLay(Layer* overlay)
    {
        m_layerStack.popOverlay(overlay);
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

        MINT_CORE_TRACE("{0}", e);

        // Top layer gets the event first. If the event wasn't handled, give the event to the next layer.
        for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
        {
            if (e.handled())
                break;
            (*it)->onEvent(e);
        }
    }


    void Application::run()
    {
        while (m_running)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_layerStack) layer->onUpdate();
            m_window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        m_running = false;

        return true;
    }


} // namespace mint
