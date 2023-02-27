#pragma once

#include "Mint/Renderer/RenderAPI.h"

namespace mint
{

    class RenderCommand
    {
      public:
        inline static void setClearColor(glm::vec4& color) { s_renderAPI->setClearColor(color); }
        inline static void clear() { s_renderAPI->clear(); }

        inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_renderAPI->drawIndexed(vertexArray);
        }

      private:
        static RenderAPI* s_renderAPI;
    };

} // namespace mint
