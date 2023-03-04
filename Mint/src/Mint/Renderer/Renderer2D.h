#pragma once

#include "Mint/Renderer/OrthographicCamera.h"
#include "Mint/Renderer/Shader.h"
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

        // Primitives
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

      private:
        struct SceneData
        {
            Ref<VertexArray> quadVertexArray;
            Ref<Shader> flatColorShader;
        };

        static SceneData* s_data;
    };

} // namespace mint
