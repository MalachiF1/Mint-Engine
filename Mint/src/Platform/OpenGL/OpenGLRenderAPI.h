#pragma once

#include "Mint/Renderer/RenderAPI.h"

namespace mint
{

    class OpenGLRenderAPI : public RenderAPI
    {
        virtual void init() override final;

        virtual void setClearColor(glm::vec4& color) override final;
        virtual void clear() override final;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override final;
    };

} // namespace mint
