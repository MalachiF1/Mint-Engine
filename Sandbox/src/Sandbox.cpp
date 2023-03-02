#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mint.h>

class ExampleLayer : public mint::Layer
{
  public:
    ExampleLayer() : Layer("Example"), m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        m_vertexArray.reset(mint::VertexArray::create());

        float vertices[] = {
            // Positions        // Colors
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.3f, 1.0f, // vertex 1
            0.5,   -0.5f, 0.0f, 0.3f, 0.8f, 0.2f, 1.0f, // vertex 2
            0.5f,  0.5f,  0.0f, 0.2f, 0.3f, 0.8f, 1.0f, // vertex 3
            -0.5f, 0.5f,  0.0f, 0.8f, 0.8f, 0.3f, 1.0f  // vertex 4
        };

        std::shared_ptr<mint::VertexBuffer> vertexBuffer =
            std::shared_ptr<mint::VertexBuffer>(mint::VertexBuffer::create(vertices, sizeof(vertices)));

        mint::BufferLayout layout = { { mint::ShaderDataType::Float3, "a_Pos" },
                                      { mint::ShaderDataType::Float4, "a_Color" } };
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
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Pos;
            out vec4 v_Color;
            
            void main()
            {
                v_Pos = a_Pos;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1);
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

        m_shader.reset(mint::Shader::create(vertexSrc, fragmentSrc));
    }

    virtual void onUpdate(mint::Timestep ts) override final
    {
        mint::RenderCommand::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
        mint::RenderCommand::clear();

        m_camera.setPosition(m_cameraPosition);
        m_camera.setRotation(m_cameraRotation);

        mint::Renderer::beginScene(m_camera);
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

  private:
    std::shared_ptr<mint::Shader> m_shader;
    std::shared_ptr<mint::VertexArray> m_vertexArray;
    mint::OrthographicCamera m_camera;
    glm::vec3 m_cameraPosition  = glm::vec3(0.0f);
    float m_cameraRotation      = 0.0f;
    float m_cameraMoveSpeed     = 1.5f;
    float m_cameraRotationSpeed = 50.0f;
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