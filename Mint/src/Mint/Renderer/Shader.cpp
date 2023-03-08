#include "mtpch.h"

#include "Shader.h"

#include "Mint/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace mint
{

Ref<Shader> Shader::create(const std::string& path)
{
    switch (Renderer::getAPI())
    {
        case RenderAPI::API::None:
            MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;

        case RenderAPI::API::OpenGL: return CreateRef<OpenGLShader>(path);
    }

    MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch (Renderer::getAPI())
    {
        case RenderAPI::API::None:
            MINT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;

        case RenderAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }

    MINT_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

void ShaderLibrary::add(const Ref<Shader>& shader)
{
    std::string name = shader->getName();
    MINT_CORE_ASSERT(m_shaders.find(name) == m_shaders.end(), "Shader already exists!");
    m_shaders[name] = shader;
}

Ref<Shader> ShaderLibrary::load(const std::string& path)
{
    auto shader = Shader::create(path);
    add(shader);
    return shader;
}

Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
    auto shader = Shader::create(name, vertexSrc, fragmentSrc);
    add(shader);
    return shader;
}

Ref<Shader> ShaderLibrary::get(const std::string& name)
{
    MINT_CORE_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shader not found!");
    return m_shaders[name];
}

} // namespace mint
