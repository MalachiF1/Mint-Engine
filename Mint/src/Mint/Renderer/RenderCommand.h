#pragma once

#include "Mint/Renderer/RenderAPI.h"

namespace mint
{

class RenderCommand
{
  public:
    inline static void init() { s_renderAPI->init(); };

    inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        s_renderAPI->setViewport(x, y, width, height);
    }

    inline static void setClearColor(glm::vec4& color) { s_renderAPI->setClearColor(color); }
    inline static void clear() { s_renderAPI->clear(); }

    inline static void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
    {
        s_renderAPI->drawIndexed(vertexArray, indexCount);
    }

  private:
    static RenderAPI* s_renderAPI;
};

} // namespace mint
