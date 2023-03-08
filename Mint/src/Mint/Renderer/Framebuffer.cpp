#include "mtpch.h"

#include "Framebuffer.h"

#include "Mint/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace mint
{

    Ref<Framebuffer> Framebuffer::create(const FramebufferSpecification& spec)
    {
        switch (Renderer::getAPI())
        {
            case RenderAPI::API::None:
                MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;

            case RenderAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
        }

        MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace mint