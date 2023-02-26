#include "mtpch.h"

#include "Application.h"

#include "Mint/Core/Input.h"
#include "Mint/Core/KeyCodes.h"

#include <glad/glad.h>

namespace mint
{

    Application* Application::s_instance = nullptr;

    // Temporary
    static GLenum shaderDataTypeToOpenGLDataType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int: return GL_INT;
            case ShaderDataType::Int2: return GL_INT;
            case ShaderDataType::Int3: return GL_INT;
            case ShaderDataType::Int4: return GL_INT;
            case ShaderDataType::Mat3: return GL_FLOAT;
            case ShaderDataType::Mat4: return GL_FLOAT;
            case ShaderDataType::Bool: return GL_BOOL;
        }

        MINT_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

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

        float vertices[] = {
            // Positions        // Colors
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // vertex 1
            0.5,   -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // vertex 2
            0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f  // vertex3
        };

        m_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = { { ShaderDataType::Float3, "a_Pos" }, { ShaderDataType::Float4, "a_Color" } };

            m_vertexBuffer->setLayout(layout);
        }

        uint32_t index     = 0;
        const auto& layout = m_vertexBuffer->getLayout();
        for (const auto& element : layout.getElements()) // layout.elements
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.getComponentCount(),
                shaderDataTypeToOpenGLDataType(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (const void*)element.offset
            );
            ++index;
        }

        uint32_t indices[] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::create(indices, std::size(indices)));


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
            glBindVertexArray(m_vertexArrray);
            glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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
