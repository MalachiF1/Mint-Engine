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

        s_data->quadVertexArray = VertexArray::create();

        Ref<VertexBuffer> quadVB = VertexBuffer::create(s_data->maxVertices * sizeof(QuadVertex));
        BufferLayout layout      = {
            {ShaderDataType::Float3, "a_Pos"},
            {ShaderDataType::Float4, "a_Color"},
            {ShaderDataType::Float2, "a_TexCoords"},
            {ShaderDataType::Float, "a_TexIndex"},
            {ShaderDataType::Float, "a_TilingFactor"},
        };
        quadVB->setLayout(layout);
        s_data->quadVertexArray->addVertexBuffer(quadVB);

        s_data->quadvertexBufferBase = new QuadVertex[s_data->maxVertices];

        // Can be huge memory allocation, therefore we allocate it on the heap.
        uint32_t* quadIndices = new uint32_t[s_data->maxIndices];
        uint32_t offset       = 0;
        for (uint32_t i = 0; i < s_data->maxIndices - 6; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;
            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }
        Ref<IndexBuffer> quadIB = IndexBuffer::create(quadIndices, s_data->maxIndices);
        delete[] quadIndices;
        s_data->quadVertexArray->setIndexBuffer(quadIB);

        s_data->whiteTexture      = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data->whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));

        int32_t samplers[s_data->maxTextureSlots];
        for (int32_t i = 0; i < s_data->maxTextureSlots; ++i) samplers[i] = i;

        s_data->textureShader = Shader::create("assets/shaders/texture.glsl");
        s_data->textureShader->bind();
        s_data->textureShader->setIntArray("u_Textures", samplers, s_data->maxTextureSlots);

        s_data->textureSlots[0] = s_data->whiteTexture;
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

        s_data->quadIndexCount      = 0;
        s_data->quadvertexBufferPtr = s_data->quadvertexBufferBase;

        s_data->textureSlotsIndex = 1;
    }

    void Renderer2D::endScene()
    {
        MINT_PROFILE_FUNCTION();

        size_t dataSize = (uint8_t*)s_data->quadvertexBufferPtr - (uint8_t*)s_data->quadvertexBufferBase;
        s_data->quadVertexArray->getVertexBuffers()[0]->setData(s_data->quadvertexBufferBase, dataSize);

        flush();
    }

    void Renderer2D::flush()
    {
        MINT_PROFILE_FUNCTION();

        for (uint32_t i = 0; i < s_data->textureSlotsIndex; ++i) s_data->textureSlots[i]->bind(i);
        RenderCommand::drawIndexed(s_data->quadVertexArray, s_data->quadIndexCount);
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        drawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        MINT_PROFILE_FUNCTION();

        const float texIndex     = 0.0f; // white texture
        const float tilingFactor = 1.0f;

        // Bottom left
        s_data->quadvertexBufferPtr->position     = position;
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = {0.0f, 0.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Bottom Right
        s_data->quadvertexBufferPtr->position     = {position.x + size.x, position.y, position.z};
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = {1.0f, 0.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Right
        s_data->quadvertexBufferPtr->position     = {position.x + size.x, position.y + size.y, position.z};
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = {1.0f, 1.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Left
        s_data->quadvertexBufferPtr->position     = {position.x, position.y + size.y, position.z};
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = {0.0f, 1.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        s_data->quadIndexCount += 6;
    }

    void Renderer2D::drawQuad(
        const glm::vec2& position,
        const glm::vec2& size,
        const Ref<Texture2D>& texture,
        float tilingFactor,
        glm::vec4 tint
    )
    {
        drawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tint);
    }

    void Renderer2D::drawQuad(
        const glm::vec3& position,
        const glm::vec2& size,
        const Ref<Texture2D>& texture,
        float tilingFactor,
        glm::vec4 tint
    )
    {
        MINT_PROFILE_FUNCTION();

        float texIndex = 0;
        for (uint32_t i = 0; i < s_data->textureSlotsIndex; ++i)
        {
            if (*s_data->textureSlots[i].get() == *texture.get())
            {
                texIndex = (float)i;
                break;
            }
        }
        if (texIndex == 0.0f)
        {
            texIndex                       = (float)s_data->textureSlotsIndex;
            s_data->textureSlots[texIndex] = texture;
            s_data->textureSlotsIndex++;
        }

        // Bottom left
        s_data->quadvertexBufferPtr->position     = position;
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = {0.0f, 0.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Bottom Right
        s_data->quadvertexBufferPtr->position     = {position.x + size.x, position.y, position.z};
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = {1.0f, 0.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Right
        s_data->quadvertexBufferPtr->position     = {position.x + size.x, position.y + size.y, position.z};
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = {1.0f, 1.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Left
        s_data->quadvertexBufferPtr->position     = {position.x, position.y + size.y, position.z};
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = {0.0f, 1.0f};
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        s_data->quadIndexCount += 6;
    }

} // namespace mint