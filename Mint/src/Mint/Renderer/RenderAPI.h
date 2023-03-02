#pragma once

#include "Mint/Renderer/VertexArray.h"

#include <glm/glm.hpp>
#include <memory>

namespace mint
{

    class RenderAPI
    {
      public:
        enum class API
        {
            None   = 0,
            OpenGL = 1,
        };

      public:
        virtual void setClearColor(glm::vec4& color) = 0;
        virtual void clear()                         = 0;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        inline static const API getAPI() { return s_API; }

      private:
        static API s_API;
    };

} // namespace mint
