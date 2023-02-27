#pragma once

#include "Mint/Renderer/RenderAPI.h"

namespace mint
{

    class OpenGLRenderAPI : public RenderAPI
    {

        virtual void setClearColor(glm::vec4& color) override;
        virtual void clear() override;

        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

} // namespace mint
