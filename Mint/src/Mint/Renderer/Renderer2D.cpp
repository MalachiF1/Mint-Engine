#include "mtpch.h"

#include "Renderer2D.h"

#include "Mint/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace mint
{

    // ======================================================================================================
    //     Initialize Renderer Data
    // ======================================================================================================

    Renderer2D::SceneData* Renderer2D::s_data = new Renderer2D::SceneData;

    void Renderer2D::init()
    {
        MINT_PROFILE_FUNCTION();

        // Quad vertex array
        // ------------
        s_data->quadVertexArray = VertexArray::create();

        // The quad vertex positions the transforms will be applied to.
        s_data->quadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_data->quadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_data->quadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        s_data->quadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

        // Quad vertex buffer
        // -------------
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

        // Quad index buffer
        // ------------

        // Can be a huge memory allocation, therefore we allocate it on the heap.
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

        // White texture (We will use this texture on color quads as it doesn't affect the final color.)
        s_data->whiteTexture      = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data->whiteTexture->setData(&whiteTextureData, sizeof(whiteTextureData));
        s_data->textureSlots[0] = s_data->whiteTexture;

        // Set up shader
        int32_t samplers[s_data->maxTextureSlots];
        for (int32_t i = 0; i < s_data->maxTextureSlots; ++i) samplers[i] = i;

        s_data->textureShader = Shader::create("assets/shaders/texture.glsl");
        s_data->textureShader->bind();
        s_data->textureShader->setIntArray("u_Textures", samplers, s_data->maxTextureSlots);
    }

    void Renderer2D::shutdown()
    {
        MINT_PROFILE_FUNCTION();

        delete[] s_data->quadvertexBufferBase;
        delete s_data;
    }


    // ======================================================================================================
    //    Scene
    // ======================================================================================================

    // Initialize scene data (ViewProjection, reset buffer data)
    // ------------------------------------------------------------------------------------------------------
    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        MINT_PROFILE_FUNCTION();

        s_data->textureShader->bind();
        s_data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());

        startBatch();
    }

    // End the scene and draw the data in the buffer
    // ------------------------------------------------------------------------------------------------------
    void Renderer2D::endScene()
    {
        MINT_PROFILE_FUNCTION();

        size_t dataSize = size_t((uint8_t*)s_data->quadvertexBufferPtr - (uint8_t*)s_data->quadvertexBufferBase);
        s_data->quadVertexArray->getVertexBuffers()[0]->setData(s_data->quadvertexBufferBase, dataSize);

        flush();
    }

    // Flush (draw) the buffer (may be called before end scene if the buffer is filled)
    void Renderer2D::flush()
    {
        MINT_PROFILE_FUNCTION();
        if (s_data->quadIndexCount == 0)
            return; // nothing to draw

        for (uint32_t i = 0; i < s_data->textureSlotsIndex; ++i) s_data->textureSlots[i]->bind(i);
        RenderCommand::drawIndexed(s_data->quadVertexArray, s_data->quadIndexCount);
    }

    void Renderer2D::startBatch()
    {
        s_data->quadIndexCount      = 0;
        s_data->quadvertexBufferPtr = s_data->quadvertexBufferBase;

        s_data->textureSlotsIndex = 1;
    }

    void Renderer2D::nextBatch()
    {
        flush();
        startBatch();
    }


    // ======================================================================================================
    //     Draw Quads
    // ======================================================================================================

    // Color Quads
    // ------------------------------------------------------------------------------------------------------

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        drawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        MINT_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::scale(transform, {size.x, size.y, 1.0f});

        drawQuad(transform, color);
    }


    // Texture Quads
    // ------------------------------------------------------------------------------------------------------

    void Renderer2D::drawQuad(
        const glm::vec2& position,
        const glm::vec2& size,
        const Ref<Texture2D>& texture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        drawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tint);
    }

    void Renderer2D::drawQuad(
        const glm::vec3& position,
        const glm::vec2& size,
        const Ref<Texture2D>& texture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::scale(transform, {size.x, size.y, 1.0f});

        drawQuad(transform, texture, tilingFactor, tint);
    }

    // SubTexture Quads
    // ------------------------------------------------------------------------------------------------------

    void Renderer2D::drawQuad(
        const glm::vec2& position,
        const glm::vec2& size,
        const Ref<SubTexture2D>& subTexture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        drawQuad({position.x, position.y, 0.0f}, size, subTexture, tilingFactor, tint);
    }

    void Renderer2D::drawQuad(
        const glm::vec3& position,
        const glm::vec2& size,
        const Ref<SubTexture2D>& subTexture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::scale(transform, {size.x, size.y, 1.0f});

        drawQuad(transform, subTexture, tilingFactor, tint);
    }


    // Rotated Color Quads
    // ------------------------------------------------------------------------------------------------------

    void Renderer2D::drawRotatedQuad(
        const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color
    )
    {
        drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
    }

    void Renderer2D::drawRotatedQuad(
        const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color
    )
    {
        MINT_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::rotate(transform, glm::radians(rotation), {0.0f, 0.0f, 1.0f});
        transform           = glm::scale(transform, {size.x, size.y, 1.0f});

        drawQuad(transform, color);
    }


    // Rotated Texture Quads
    // ------------------------------------------------------------------------------------------------------

    void Renderer2D::drawRotatedQuad(
        const glm::vec2& position,
        const glm::vec2& size,
        float rotation,
        const Ref<Texture2D>& texture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tint);
    }

    void Renderer2D::drawRotatedQuad(
        const glm::vec3& position,
        const glm::vec2& size,
        float rotation,
        const Ref<Texture2D>& texture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        MINT_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::rotate(transform, glm::radians(rotation), {0.0f, 0.0f, 1.0f});
        transform           = glm::scale(transform, {size.x, size.y, 1.0f});

        drawQuad(transform, texture, tilingFactor, tint);
    }


    // Rotated SubTexture Quads
    // ------------------------------------------------------------------------------------------------------

    void Renderer2D::drawRotatedQuad(
        const glm::vec2& position,
        const glm::vec2& size,
        float rotation,
        const Ref<SubTexture2D>& subTexture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        drawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, subTexture, tilingFactor, tint);
    }

    void Renderer2D::drawRotatedQuad(
        const glm::vec3& position,
        const glm::vec2& size,
        float rotation,
        const Ref<SubTexture2D>& subTexture,
        float tilingFactor,
        const glm::vec4& tint
    )
    {
        MINT_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform           = glm::rotate(transform, glm::radians(rotation), {0.0f, 0.0f, 1.0f});
        transform           = glm::scale(transform, {size.x, size.y, 1.0f});

        drawQuad(transform, subTexture, tilingFactor, tint);
    }


    // Draw Quad Implementation
    // ------------------------------------------------------------------------------------------------------

    void Renderer2D::drawQuad(const glm::mat4& transform, const glm::vec4& color)
    {

        MINT_PROFILE_FUNCTION();

        if (s_data->quadIndexCount + 6 >= s_data->maxIndices)
            nextBatch();

        const float texIndex        = 0.0f; // white texture
        const float tilingFactor    = 1.0f;
        const glm::vec2 texCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

        // Bottom left
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[0];
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[0];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Bottom Right
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[1];
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[1];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Right
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[2];
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[2];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Left
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[3];
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->color        = color;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[3];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        s_data->quadIndexCount += 6;
    }

    void Renderer2D::drawQuad(
        const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tint
    )
    {
        MINT_PROFILE_FUNCTION();

        if (s_data->quadIndexCount + 6 >= s_data->maxIndices)
            nextBatch();

        const glm::vec2 texCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

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
            if (s_data->textureSlotsIndex >= s_data->maxTextureSlots)
                nextBatch();

            texIndex                       = (float)s_data->textureSlotsIndex;
            s_data->textureSlots[texIndex] = texture;
            s_data->textureSlotsIndex++;
        }

        // Bottom left
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[0];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[0];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Bottom Right
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[1];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[1];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Right
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[2];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[2];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Left
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[3];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[3];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        s_data->quadIndexCount += 6;
    }

    void Renderer2D::drawQuad(
        const glm::mat4& transform, const Ref<SubTexture2D>& subTexture, float tilingFactor, const glm::vec4& tint
    )
    {
        MINT_PROFILE_FUNCTION();

        if (s_data->quadIndexCount + 6 >= s_data->maxIndices)
            nextBatch();

        const glm::vec2* texCoords = subTexture->getTexCoords();

        float texIndex = 0;
        for (uint32_t i = 0; i < s_data->textureSlotsIndex; ++i)
        {
            if (*s_data->textureSlots[i].get() == *subTexture->getTexture().get())
            {
                texIndex = (float)i;
                break;
            }
        }
        if (texIndex == 0.0f)
        {
            if (s_data->textureSlotsIndex >= s_data->maxTextureSlots)
                nextBatch();

            texIndex                       = (float)s_data->textureSlotsIndex;
            s_data->textureSlots[texIndex] = subTexture->getTexture();
            s_data->textureSlotsIndex++;
        }

        // Bottom left
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[0];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[0];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Bottom Right
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[1];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[1];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Right
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[2];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[2];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        // Top Left
        s_data->quadvertexBufferPtr->position     = transform * s_data->quadVertexPositions[3];
        s_data->quadvertexBufferPtr->color        = tint;
        s_data->quadvertexBufferPtr->texCoords    = texCoords[3];
        s_data->quadvertexBufferPtr->texIndex     = texIndex;
        s_data->quadvertexBufferPtr->tilingFactor = tilingFactor;
        s_data->quadvertexBufferPtr++;

        s_data->quadIndexCount += 6;
    }

} // namespace mint