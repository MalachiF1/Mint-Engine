#include "mtpch.h"

#include "VertexArray.h"

#include "Mint/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace mint
{
    VertexArray* VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
            case RenderAPI::API::None:
                MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;

            case RenderAPI::API::OpenGL: return new OpenGLVertexArray();
        }

        MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    }
} // namespace mint