#pragma once

#include "Mint/Renderer/RenderAPI.h"

namespace mint
{

class OpenGLRenderAPI final : public RenderAPI
{
    virtual void init() override;

    virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    virtual void setClearColor(glm::vec4& color) override;
    virtual void clear() override;

    virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
};

} // namespace mint
