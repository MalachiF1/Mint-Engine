#include "mtpch.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace mint
{

    Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData;

    void Renderer::init() {
        RenderCommand::init();
    }

    void Renderer::beginScene(OrthographicCamera& camera)
    {
        m_sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {}


    void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4(
            "u_ViewProjection", m_sceneData->viewProjectionMatrix
        );
        std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniformMat4("u_Transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

} // namespace mint