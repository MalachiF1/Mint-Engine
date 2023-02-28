#pragma once

#include "Mint/Renderer/OrthographicCamera.h"
#include "Mint/Renderer/RenderCommand.h"
#include "Mint/Renderer/Shader.h"

namespace mint
{

    class Renderer
    {
      public:
        static void beginScene(OrthographicCamera& camera);
        static void endScene();

        static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

        inline static RenderAPI::API getAPI() { return RenderAPI::getAPI(); }

      private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
        };
        static SceneData* m_sceneData;
    };

} // namespace mint
