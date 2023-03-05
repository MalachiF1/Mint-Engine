#include "mtpch.h"

#include "Renderer2D.h"

#include "Mint/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace mint
{

    Renderer2D::SceneData* Renderer2D::s_data = new Renderer2D::SceneData;

    void Renderer2D::init()
    {
        MINT_PROFILE_FUNCTION();

        float squareVertices[] = {
            // Positions        // TexCoords
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // vertex 1
            0.5,   -0.5f, 0.0f, 1.0f, 0.0f, // vertex 2
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // vertex 3
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  // vertex 4
        };

        uint32_t squareIndices[] = {
            0, 1, 2, // triangle 1
            2, 3, 0  // triangle 2
        };

        s_data->quadVertexArray = VertexArray::create();

        Ref<VertexBuffer> vertexBuffer = VertexBuffer::create(squareVertices, sizeof(squareVertices));
        BufferLayout layout = { { ShaderDataType::Float3, "a_Pos" }, { ShaderDataType::Float2, "a_TexCoords" } };
        vertexBuffer->setLayout(layout);

        s_data->quadVertexArray->addVertexBuffer(vertexBuffer);

        Ref<IndexBuffer> indexBuffer = IndexBuffer::create(squareIndices, (uint32_t)std::size(squareIndices));

        s_data->quadVertexArray->setIndexBuffer(indexBuffer);

        s_data->whiteTexture      = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data->whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

        s_data->textureShader = Shader::create("assets/shaders/texture.glsl");
    }

    void Renderer2D::shutdown()
    {
        MINT_PROFILE_FUNCTION();

        delete s_data;
    }

    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        MINT_PROFILE_FUNCTION();

        s_data->textureShader->bind();
        s_data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
        s_data->textureShader->setInt("u_Texture", 0);
    }

    void Renderer2D::endScene()
    {
        MINT_PROFILE_FUNCTION();
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
    {
        drawQuad({ position.x, position.y, 0.0f }, size, color, rotation);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
    {
        MINT_PROFILE_FUNCTION();

        s_data->whiteTexture->bind();

        s_data->textureShader->setFloat4("u_Color", color);
        s_data->textureShader->setFloat("u_TilingFactor", 1.0f);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform           = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        s_data->textureShader->setMat4("u_Transform", transform);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

    void Renderer2D::drawQuad(
        const glm::vec2& position,
        const glm::vec2& size,
        const Ref<Texture2D>& texture,
        float rotation,
        float tilingFactor,
        glm::vec4 tint
    )
    {
        drawQuad({ position.x, position.y, 0.0f }, size, texture, rotation, tilingFactor, tint);
    }

    void Renderer2D::drawQuad(
        const glm::vec3& position,
        const glm::vec2& size,
        const Ref<Texture2D>& texture,
        float rotation,
        float tilingFactor,
        glm::vec4 tint
    )
    {
        MINT_PROFILE_FUNCTION();

        texture->bind();

        s_data->textureShader->setFloat4("u_Color", tint);
        s_data->textureShader->setFloat("u_TilingFactor", tilingFactor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform           = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        s_data->textureShader->setMat4("u_Transform", transform);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

} // namespace mint