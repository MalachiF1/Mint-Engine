#pragma once

#include "Mint/Renderer/OrthographicCamera.h"
#include "Mint/Renderer/Shader.h"
#include "Mint/Renderer/Texture.h"
#include "Mint/Renderer/VertexArray.h"

namespace mint
{

    class Renderer2D
    {
      public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void flush();

        // Primitives
        // ----------

        // Color quads
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        // Texture quads
        static void drawQuad(
            const glm::vec2& position,
            const glm::vec2& size,
            const Ref<Texture2D>& texture,
            float tilingFactor    = 1.0f,
            const glm::vec4& tint = glm::vec4(1.0f)
        );
        static void drawQuad(
            const glm::vec3& position,
            const glm::vec2& size,
            const Ref<Texture2D>& texture,
            float tilingFactor    = 1.0f,
            const glm::vec4& tint = glm::vec4(1.0f)
        );

        // Rotation incurs extra runtime cost, and we usually don't need rotation, so it's separated into a different
        // method.

        // Rotated color quads
        static void drawRotatedQuad(
            const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color
        );
        static void drawRotatedQuad(
            const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color
        );
        // Rotated texture quads
        static void drawRotatedQuad(
            const glm::vec2& position,
            const glm::vec2& size,
            float rotation,
            const Ref<Texture2D>& texture,
            float tilingFactor    = 1.0f,
            const glm::vec4& tint = glm::vec4(1.0f)
        );
        static void drawRotatedQuad(
            const glm::vec3& position,
            const glm::vec2& size,
            float rotation,
            const Ref<Texture2D>& texture,
            float tilingFactor    = 1.0f,
            const glm::vec4& tint = glm::vec4(1.0f)
        );

        // Draw quads from transforms (the previous overloads call these methods)
        static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
        static void drawQuad(
            const glm::mat4& transform,
            const Ref<Texture2D>& texture,
            float tilingFactor    = 1.0f,
            const glm::vec4& tint = glm::vec4(1.0f)
        );

      private:
        static void startBatch();
        static void nextBatch();

      private:
        // Renderer data
        // -------------

        // Quad vertex structure
        struct QuadVertex
        {
            glm::vec3 position;
            glm::vec4 color;
            glm::vec2 texCoords;
            float texIndex;
            float tilingFactor;
        };

        struct SceneData
        {
            // Max data buffer can hold (we will flush the buffer if this is reached).
            static const uint32_t maxQuads        = 10000;
            static const uint32_t maxVertices     = maxQuads * 4;
            static const uint32_t maxIndices      = maxQuads * 6;
            static const uint32_t maxTextureSlots = 32; // TODO:: check driver capablities per device

            Ref<VertexArray> quadVertexArray;
            Ref<Shader> textureShader;
            Ref<Texture2D> whiteTexture; // A white texture that doesn't affect final color

            uint32_t quadIndexCount          = 0;
            QuadVertex* quadvertexBufferBase = nullptr; // The buffer that holds all our vertex data
            QuadVertex* quadvertexBufferPtr  = nullptr; // A pointer to the next vertex we need to fill

            // A map of what texture we have at what slot (index = slot)
            std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
            // The index of the next slot to fill (index 0 is our white texture)
            uint32_t textureSlotsIndex = 1;

            // The vertex positions all our quad positions will be based on
            glm::vec4 quadVertexPositions[4];
        };

        static SceneData* s_data;
    };

} // namespace mint
