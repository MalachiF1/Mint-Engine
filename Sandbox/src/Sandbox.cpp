#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <mint.h>

class ExampleLayer : public mint::Layer
{
  public:
    ExampleLayer() :
        Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_squareColor(glm::vec4(0.5f, 0.5f, 0.8f, 1.0f))
    {
        m_vertexArray.reset(mint::VertexArray::create());

        float vertices[] = {
            // Positions
            -0.5f, -0.5f, 0.0f, // vertex 1
            0.5,   -0.5f, 0.0f, // vertex 2
            0.5f,  0.5f,  0.0f, // vertex 3
            -0.5f, 0.5f,  0.0f, // vertex 4
        };

        std::shared_ptr<mint::VertexBuffer> vertexBuffer =
            std::shared_ptr<mint::VertexBuffer>(mint::VertexBuffer::create(vertices, sizeof(vertices)));

        mint::BufferLayout layout = {
            { mint::ShaderDataType::Float3, "a_Pos" },
        };
        vertexBuffer->setLayout(layout);
        m_vertexArray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {
            0, 1, 2, // triangle 1
            2, 3, 0  // triangle 2
        };

        std::shared_ptr<mint::IndexBuffer> indexBuffer =
            std::shared_ptr<mint::IndexBuffer>(mint::IndexBuffer::create(indices, std::size(indices)));

        m_vertexArray->setIndexBuffer(indexBuffer);


        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Pos;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Pos;
            
            void main()
            {
                v_Pos = a_Pos;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec4 u_Color;

            in vec3 v_Pos;
            in vec4 v_Color;
            
            void main()
            {
                color = u_Color;
            }
        )";

        m_shader.reset(mint::Shader::create(vertexSrc, fragmentSrc));
    }

    virtual void onUpdate(mint::Timestep ts) override final
    {
        mint::RenderCommand::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
        mint::RenderCommand::clear();

        m_camera.setPosition(m_cameraPosition);
        m_camera.setRotation(m_cameraRotation);

        mint::Renderer::beginScene(m_camera);

        std::dynamic_pointer_cast<mint::OpenGLShader>(m_shader)->bind();
        std::dynamic_pointer_cast<mint::OpenGLShader>(m_shader)->setUniformFloat4("u_Color", m_squareColor);

        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
                transform           = glm::scale(transform, glm::vec3(0.1f));
                mint::Renderer::submit(m_shader, m_vertexArray, transform);
            }
        }

        mint::Renderer::endScene();

        // Camera Movement
        if (mint::Input::isKeyPressed(MINT_KEY_W))
            m_cameraPosition.y += m_cameraMoveSpeed * ts;

        if (mint::Input::isKeyPressed(MINT_KEY_S))
            m_cameraPosition.y -= m_cameraMoveSpeed * ts;

        if (mint::Input::isKeyPressed(MINT_KEY_D))
            m_cameraPosition.x += m_cameraMoveSpeed * ts;

        if (mint::Input::isKeyPressed(MINT_KEY_A))
            m_cameraPosition.x -= m_cameraMoveSpeed * ts;

        if (mint::Input::isKeyPressed(MINT_KEY_E))
            m_cameraRotation -= m_cameraRotationSpeed * ts;

        if (mint::Input::isKeyPressed(MINT_KEY_Q))
            m_cameraRotation += m_cameraRotationSpeed * ts;
    }

    virtual void onImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_squareColor));
        ImGui::End();
    }

  private:
    std::shared_ptr<mint::Shader> m_shader;
    std::shared_ptr<mint::VertexArray> m_vertexArray;
    mint::OrthographicCamera m_camera;
    glm::vec3 m_cameraPosition  = glm::vec3(0.0f);
    float m_cameraRotation      = 0.0f;
    float m_cameraMoveSpeed     = 1.5f;
    float m_cameraRotationSpeed = 50.0f;

    glm::vec4 m_squareColor;
};

class Sandbox : public mint::Application
{
  public:
    Sandbox() { pushLayer(new ExampleLayer); }

    virtual ~Sandbox() final {}
};


mint::Application* mint::createApplication()
{
    return new Sandbox();
}