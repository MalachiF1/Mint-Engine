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


        glGenVertexArrays(1, &m_vertexArrray);
        glBindVertexArray(m_vertexArrray);

        float vertices[] = { -0.5f, -0.5f, 0.0f, 0.5, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
        m_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::create(indices, std::size(indices)));


        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Pos;

            out vec3 v_Pos;
            
            void main()
            {
                v_Pos = a_Pos;
                gl_Position = vec4(a_Pos, 1);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Pos;
            
            void main()
            {
                color = vec4(v_Pos * 0.5 + 0.5, 1.0);
            }
        )";

        m_shader.reset(Shader::create(vertexSrc, fragmentSrc));
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
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->bind();
            glBindVertexArray(m_vertexArrray);
            glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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
