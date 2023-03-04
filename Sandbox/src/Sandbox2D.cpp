#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <memory>


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_cameraController(1200.0f / 720.0f, true)
{
    m_checkerboardTexture = mint::Texture2D::create("assets/textures/Checkerboard.png");
}

void Sandbox2D::onAttach() {}

void Sandbox2D::onDetach() {}

void Sandbox2D::onUpdate(mint::Timestep ts)
{
    m_cameraController.onUpdate(ts);

    mint::RenderCommand::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    mint::RenderCommand::clear();

    mint::Renderer2D::beginScene(m_cameraController.getCamera());
    mint::Renderer2D::drawQuad({ 0.3f, 0.3f, 0.1f }, { 0.5f, 1.5f }, m_color, 45.0f);
    mint::Renderer2D::drawQuad({ 0.0f, 0.5f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
    mint::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 8.0f, 8.0f }, m_checkerboardTexture);
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
