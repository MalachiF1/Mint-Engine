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


        m_vertexArrray.reset(VertexArray::create());

        float vertices[] = {
            // Positions        // Colors
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f, // vertex 1
            0.5,   -0.5f, 0.0f, 0.3f, 0.8f, 0.2f, 1.0f, // vertex 2
            0.5f,  0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f, // vertex 3
            -0.5f, 0.5f,  0.0f, 0.8f, 0.8f, 0.3f, 1.0f  // vertex 4
        };

        std::shared_ptr<VertexBuffer> vertexBuffer =
            std::shared_ptr<VertexBuffer>(VertexBuffer::create(vertices, sizeof(vertices)));

        BufferLayout layout = { { ShaderDataType::Float3, "a_Pos" }, { ShaderDataType::Float4, "a_Color" } };
        vertexBuffer->setLayout(layout);
        m_vertexArrray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {
            0, 1, 2, // triangle 1
            2, 3, 0  // triangle 2
        };

        std::shared_ptr<IndexBuffer> indexBuffer =
            std::shared_ptr<IndexBuffer>(IndexBuffer::create(indices, std::size(indices)));

        m_vertexArrray->setIndexBuffer(indexBuffer);


        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Pos;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Pos;
            out vec4 v_Color;
            
            void main()
            {
                v_Pos = a_Pos;
                v_Color = a_Color;
                gl_Position = vec4(a_Pos, 1);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Pos;
            in vec4 v_Color;
            
            void main()
            {
                color = v_Color;
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
            m_vertexArrray->bind();
            glDrawElements(GL_TRIANGLES, m_vertexArrray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

            for (auto layer : m_layerStack.getLayers()) { layer->onUpdate(); }

            m_ImGuiLayer->begin();
            for (auto layer : m_layerStack.getLayers()) { layer->onImGuiRender(); }
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
