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
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(
            const glm::vec2& position,
            const glm::vec2& size,
            const Ref<Texture2D>& texture,
            float tilingFactor = 1.0f,
            glm::vec4 tint     = glm::vec4(1.0f)
        );
        static void drawQuad(
            const glm::vec3& position,
            const glm::vec2& size,
            const Ref<Texture2D>& texture,
            float tilingFactor = 1.0f,
            glm::vec4 tint     = glm::vec4(1.0f)
        );

      private:
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
            const uint32_t maxQuads               = 10000;
            const uint32_t maxVertices            = maxQuads * 4;
            const uint32_t maxIndices             = maxQuads * 6;
            static const uint32_t maxTextureSlots = 32; // TODO:: check driver capablities per device

            Ref<VertexArray> quadVertexArray;
            Ref<Shader> textureShader;
            Ref<Texture2D> whiteTexture;

            uint32_t quadIndexCount          = 0;
            QuadVertex* quadvertexBufferBase = nullptr;
            QuadVertex* quadvertexBufferPtr  = nullptr;

            std::array<Ref<Texture2D>, maxTextureSlots> textureSlots;
            uint32_t textureSlotsIndex = 1; // slot 0 is our white texture
        };

        static SceneData* s_data;
    };

} // namespace mint
