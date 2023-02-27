#pragma once

#include "Mint/Renderer/RenderCommand.h"

namespace mint
{

    class Renderer
    {
      public:
        static void beginScene();
        static void endScene();

        static void submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RenderAPI::API getAPI() { return RenderAPI::getAPI(); }
    };

} // namespace mint
