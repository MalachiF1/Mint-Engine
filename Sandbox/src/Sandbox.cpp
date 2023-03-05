#include "Sandbox2D.h"

#include <Mint.h>
#include <Mint/Core/EntryPoint.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

class ExampleLayer : public mint::Layer
{
  public:
    ExampleLayer() :
        Layer("Example"), m_cameraController(1200.0f / 720.0f, true), m_squareColor(glm::vec4(0.5f, 0.5f, 0.8f, 1.0f))
    {
        m_vertexArray = mint::VertexArray::create();

        float vertices[] = {
            // Positions        // TexCoords
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // vertex 1
            0.5,   -0.5f, 0.0f, 1.0f, 0.0f, // vertex 2
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // vertex 3
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // vertex 4
        };

        mint::Ref<mint::VertexBuffer> vertexBuffer = mint::VertexBuffer::create(vertices, sizeof(vertices));

        mint::BufferLayout layout = {
            {mint::ShaderDataType::Float3, "a_Pos"},
            {mint::ShaderDataType::Float2, "a_TexCoords"},
        };
        vertexBuffer->setLayout(layout);
        m_vertexArray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {0, 1, 2, 2, 3, 0};

        mint::Ref<mint::IndexBuffer> indexBuffer = mint::IndexBuffer::create(indices, (uint32_t)std::size(indices));

        m_vertexArray->setIndexBuffer(indexBuffer);


        std::string flatColorVertexSrc = R"(
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

        std::string flatColorFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec4 u_Color;

            in vec3 v_Pos;
            
            void main()
            {
                color = u_Color;
            }
        )";

        m_shaderLibrary.load("flatColor", flatColorVertexSrc, flatColorFragmentSrc);

        auto textureShader = m_shaderLibrary.load("assets/shaders/texture.glsl");

        m_checkerboardTexture = mint::Texture2D::create("assets/textures/Checkerboard.png");
        m_awesomefaceTexture  = mint::Texture2D::create("assets/textures/awesomeface.png");

        textureShader->bind();
        textureShader->setInt("u_Texture", 0);
    }

    virtual void onUpdate(mint::Timestep ts) override final
    {
        m_cameraController.onUpdate(ts);

        mint::RenderCommand::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        mint::RenderCommand::clear();

        mint::Renderer::beginScene(m_cameraController.getCamera());

        auto flatColorShader = m_shaderLibrary.get("flatColor");
        flatColorShader->bind();
        flatColorShader->setFloat4("u_Color", m_squareColor);

        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
                transform           = glm::scale(transform, glm::vec3(0.1f));
                mint::Renderer::submit(flatColorShader, m_vertexArray, transform);
            }
        }

        auto textureShader = m_shaderLibrary.get("texture");
        m_checkerboardTexture->bind(0);
        mint::Renderer::submit(textureShader, m_vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_awesomefaceTexture->bind(0);
        mint::Renderer::submit(textureShader, m_vertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        mint::Renderer::endScene();
    }

    virtual void onEvent(mint::Event& e) override { m_cameraController.onEvent(e); }

    virtual void onImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_squareColor));
        ImGui::End();
    }

  private:
    mint::ShaderLibrary m_shaderLibrary; // will be moved to renderer
    mint::Ref<mint::Texture2D> m_checkerboardTexture, m_awesomefaceTexture;
    mint::Ref<mint::VertexArray> m_vertexArray;
    mint::OrthographicCameraController m_cameraController;

    glm::vec4 m_squareColor;
};

class Sandbox : public mint::Application
{
  public:
    Sandbox()
    {
        // pushLayer(new ExampleLayer());
        pushLayer(new Sandbox2D());
    }

    virtual ~Sandbox() final {}
};


mint::Application* mint::createApplication()
{
    return new Sandbox();
}