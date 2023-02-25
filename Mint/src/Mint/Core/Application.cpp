#include "mtpch.h"

#include "Application.h"

#include "Mint/Core/Input.h"
#include "Mint/Core/KeyCodes.h"

#include <glad/glad.h>

namespace mint
{

    Application* Application::s_instance = nullptr;

    Application::Application()
    {
        MINT_CORE_ASSERT(!s_instance, "There can only be one Application instance!");
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(MINT_BIND_EVENT_FN(Application::onEvent));

        m_ImGuiLayer = new ImGuiLayer();
        pushOverlay(m_ImGuiLayer);
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

    void Application::pushOverlay(Layer* overlay)
    {
        m_layerStack.pushOverlay(overlay);
    }

    void Application::popOverlay(Layer* overlay)
    {
        m_layerStack.popOverlay(overlay);
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(MINT_BIND_EVENT_FN(Application::onWindowClose));

        // MINT_CORE_TRACE("{0}", e);

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

            for (Layer* layer : m_layerStack.m_layers) { layer->onUpdate(); }

            m_ImGuiLayer->begin();
            for (Layer* layer : m_layerStack.m_layers) { layer->onImGuiRender(); }
            m_ImGuiLayer->end();

            m_window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        m_running = false;

        return true;
    }


} // namespace mint
