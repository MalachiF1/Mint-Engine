#include "mtpch.h"

#include "Application.h"

#include "Mint/Core/Timestep.h"
#include "Mint/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace mint
{

Application* Application::s_instance = nullptr;

Application::Application(const std::string& name)
{
    MINT_PROFILE_FUNCTION();

    MINT_CORE_ASSERT(!s_instance, "There can only be one Application instance!");
    s_instance = this;

    m_window = Scope<Window>(Window::create(WindowProps(name)));
    m_window->setEventCallback(MINT_BIND_EVENT_FN(Application::onEvent));

    Renderer::init();

    m_ImGuiLayer = new ImGuiLayer();
    pushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
    MINT_PROFILE_FUNCTION();

    Renderer::shutdown();
}


void Application::pushLayer(Layer* layer)
{
    MINT_PROFILE_FUNCTION();

    m_layerStack.pushLayer(layer);
}

void Application::popLayer(Layer* layer)
{
    MINT_PROFILE_FUNCTION();

    m_layerStack.popLayer(layer);
}

void Application::pushOverlay(Layer* overlay)
{
    MINT_PROFILE_FUNCTION();

    m_layerStack.pushOverlay(overlay);
}

void Application::popOverlay(Layer* overlay)
{
    MINT_PROFILE_FUNCTION();

    m_layerStack.popOverlay(overlay);
}

void Application::onEvent(Event& e)
{
    MINT_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(MINT_BIND_EVENT_FN(Application::onWindowClose));
    dispatcher.dispatch<WindowResizeEvent>(MINT_BIND_EVENT_FN(Application::onWindowResize));

    // Top layer gets the event first. If the event wasn't handled, give the event to the next layer.
    for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
    {
        if (e.isHandled())
            break;
        (*it)->onEvent(e);
    }
}

void Application::run()
{
    MINT_PROFILE_FUNCTION();

    while (m_running)
    {
        MINT_PROFILE_SCOPE("RunLoop");

        float currentTime = (float)glfwGetTime(); // implementation will move to Platform
        Timestep timestep = currentTime - m_lastFrameTime;
        m_lastFrameTime   = currentTime;

        if (!m_minimized)
        {
            MINT_PROFILE_SCOPE("Layerstack OnUpdate");

            for (auto layer : m_layerStack.getLayers()) { layer->onUpdate(timestep); }
        }

        m_ImGuiLayer->begin();
        {
            MINT_PROFILE_SCOPE("Layerstack OnImGuiRender");

            for (auto layer : m_layerStack.getLayers()) { layer->onImGuiRender(); }
        }
        m_ImGuiLayer->end();

        m_window->onUpdate();
    }
}

void Application::shutdown()
{
    MINT_PROFILE_FUNCTION();
    m_running = false;
}

bool Application::onWindowClose(WindowCloseEvent& e)
{
    m_running = false;

    return true;
}

bool Application::onWindowResize(WindowResizeEvent& e)
{
    MINT_PROFILE_FUNCTION();

    if (e.getWidth() == 0 || e.getHeight() == 0)
    {
        m_minimized = true;
        return false;
    }

    m_minimized = false;
    Renderer::onWindowResize(e.getWidth(), e.getHeight());
    return false;
}

} // namespace mint
