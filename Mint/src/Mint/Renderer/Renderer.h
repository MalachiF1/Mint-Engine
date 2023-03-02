#pragma once

#include "Mint/Renderer/OrthographicCamera.h"
#include "Mint/Renderer/RenderCommand.h"
#include "Mint/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace mint
{

    class Renderer
    {
      public:
        static void beginScene(OrthographicCamera& camera);
        static void endScene();

        static void submit(
            const std::shared_ptr<Shader>& shader,
            const std::shared_ptr<VertexArray>& vertexArray,
            const glm::mat4& transform = glm::mat4(1.0f)
        );

        inline static RenderAPI::API getAPI() { return RenderAPI::getAPI(); }

      private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
        };
        static SceneData* m_sceneData;
    };

} // namespace mint
