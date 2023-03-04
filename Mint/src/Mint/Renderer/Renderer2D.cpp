#include "mtpch.h"

#include "Renderer2D.h"

#include "Mint/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace mint
{

    Renderer2D::SceneData* Renderer2D::s_data = new Renderer2D::SceneData;

    void Renderer2D::init()
    {
        float squareVertices[] = {
            // Positions
            -0.5f, -0.5f, 0.0f, // vertex 1
            0.5,   -0.5f, 0.0f, // vertex 2
            0.5f,  0.5f,  0.0f, // vertex 3
            -0.5f, 0.5f,  0.0f, // vertex 4
        };

        uint32_t squareIndices[] = {
            0, 1, 2, // triangle 1
            2, 3, 0  // triangle 2
        };

        s_data->quadVertexArray = VertexArray::create();

        Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(squareVertices, sizeof(squareVertices));
        BufferLayout layout            = { { ShaderDataType::Float3, "a_Pos" } };
        vertexBuffer->setLayout(layout);

        s_data->quadVertexArray->addVertexBuffer(vertexBuffer);

        Ref<IndexBuffer> indexBuffer = IndexBuffer::create(squareIndices, (uint32_t)std::size(squareIndices));

        s_data->quadVertexArray->setIndexBuffer(indexBuffer);

        s_data->flatColorShader = Shader::create("assets/shaders/flatColor.glsl");
    }

    void Renderer2D::shutdown()
    {
        delete s_data;
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        s_data->flatColorShader->bind();
        s_data->flatColorShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {}

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
    {
        drawQuad({ position.x, position.y, 0.0f }, size, color, rotation);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
    {
        s_data->flatColorShader->bind();
        s_data->flatColorShader->setFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform           = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        s_data->flatColorShader->setMat4("u_Transform", transform);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

} // namespace mint