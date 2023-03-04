#include "Sandbox2D.h"

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <memory>

void Sandbox2D::onAttach() {}

void Sandbox2D::onDetach() {}

void Sandbox2D::onUpdate(mint::Timestep ts)
{
    m_cameraController.onUpdate(ts);

    mint::RenderCommand::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    mint::RenderCommand::clear();

    mint::Renderer2D::beginScene(m_cameraController.getCamera());
    mint::Renderer2D::drawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_color);
    mint::Renderer2D::endScene();
}

void Sandbox2D::onEvent(mint::Event& e)
{
    m_cameraController.onEvent(e);
}

void Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Sqaure Color", glm::value_ptr(m_color));
    ImGui::End();
}
