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
            case RendererAPI::None:
                MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;

            case RendererAPI::OpenGL: return new OpenGLVertexArray();
        }

        MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    }
} // namespace mint