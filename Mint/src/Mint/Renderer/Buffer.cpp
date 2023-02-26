#include "mtpch.h"

#include "Buffer.h"

#include "Mint/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace mint
{
    // Vertex Buffer
    // ----------------------------------------------------------------------------

    VertexBuffer* VertexBuffer::create(float* vertices, size_t size)
    {
        switch (Renderer::getAPI())
        {
            case RendererAPI::None:
                MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;

            case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }

        MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    }

    // Index Buffer
    // ----------------------------------------------------------------------------

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
            case RendererAPI::None:
                MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;

            case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
        }

        MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    }

} // namespace mint