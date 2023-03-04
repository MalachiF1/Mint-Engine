#include "mtpch.h"

#include "Renderer.h"

#include "Mint/Renderer/Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace mint
{

     Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

    void Renderer::init()
    {
        RenderCommand::init();
        Renderer2D::init();
    }

    void Renderer::onWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::setViewport(0, 0, width, height);
    }

    void Renderer::beginScene(OrthographicCamera& camera)
    {
        s_sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {}


    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4(
            "u_ViewProjection", s_sceneData->viewProjectionMatrix
        );
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_Transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

} // namespace mint