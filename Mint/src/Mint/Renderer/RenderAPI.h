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
    virtual ~RenderAPI() = default;

    virtual void init() = 0;

    virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

    virtual void setClearColor(glm::vec4& color) = 0;
    virtual void clear()                         = 0;

    virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

    inline static const API getAPI() { return s_API; }

  private:
    static API s_API;
};

} // namespace mint
