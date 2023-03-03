#include "mtpch.h"

#include "Shader.h"

#include "Mint/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace mint
{

    Ref<Shader> Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
            case RenderAPI::API::None:
                MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;

            case RenderAPI::API::OpenGL: return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
} // namespace mint