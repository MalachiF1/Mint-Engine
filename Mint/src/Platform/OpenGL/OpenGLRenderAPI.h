#pragma once

#include "Mint/Renderer/RenderAPI.h"

namespace mint
{

    class OpenGLRenderAPI : public RenderAPI
    {
        virtual void init() override final;

        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override final;

        virtual void setClearColor(glm::vec4& color) override final;
        virtual void clear() override final;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override final;
    };

} // namespace mint
