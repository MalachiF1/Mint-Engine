#pragma once

#include "Mint/Renderer/RenderAPI.h"

namespace mint
{

    class OpenGLRenderAPI : public RenderAPI
    {

        virtual void setClearColor(glm::vec4& color) override final;
        virtual void clear() override final;

        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override final;
    };

} // namespace mint
