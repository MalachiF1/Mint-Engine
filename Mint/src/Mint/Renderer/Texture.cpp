#include "mtpch.h"

#include "Texture.h"

#include "Mint/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace mint
{

Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
{
    switch (Renderer::getAPI())
    {
        case RenderAPI::API::None:
            MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;

        case RenderAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
    }

    MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<Texture2D> Texture2D::create(const std::string& path)
{
    switch (Renderer::getAPI())
    {
        case RenderAPI::API::None:
            MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;

        case RenderAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
    }

    MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace mint
