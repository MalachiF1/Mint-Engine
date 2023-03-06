#include "Sandbox2D.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <memory>


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_cameraController(1200.0f / 720.0f, true)
{
    MINT_PROFILE_FUNCTION();

    m_checkerboardTexture = mint::Texture2D::create("assets/textures/Checkerboard.png");
}

void Sandbox2D::onAttach()
{
    MINT_PROFILE_FUNCTION();
}

void Sandbox2D::onDetach()
{
    MINT_PROFILE_FUNCTION();
}

void Sandbox2D::onUpdate(mint::Timestep ts)
{
    MINT_PROFILE_FUNCTION();

    m_cameraController.onUpdate(ts);

    {
        MINT_PROFILE_SCOPE("Renderer Prep");

        mint::RenderCommand::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        mint::RenderCommand::clear();
    }

    {
        MINT_PROFILE_SCOPE("Renderer Draw");
        static float rotation = 0.0f;
        rotation += ts * 40.0f;

        mint::Renderer2D::beginScene(m_cameraController.getCamera());
        mint::Renderer2D::drawQuad({0.0f, 0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
        mint::Renderer2D::drawQuad(
            {0.0f, 0.0f, -0.1f}, {8.0f, 8.0f}, m_checkerboardTexture, 10.0f, {1.0f, 1.0f, 0.8f, 1.0f}
        );
        mint::Renderer2D::drawRotatedQuad(
            {-0.5f, -0.5f, 0.2}, {1.0f, 1.0f}, rotation, m_checkerboardTexture, 20.0f, {8.0f, 1.0f, 1.0f, 1.0f}
        );
        mint::Renderer2D::drawQuad({0.3f, 0.3f, 0.1f}, {0.9f, 0.3f}, m_color);
        mint::Renderer2D::drawRotatedQuad({0.9f, 0.1f, 0.3f}, {3.0f, 0.5f}, 45.0f, m_color);
        mint::Renderer2D::endScene();
    }
}

void Sandbox2D::onEvent(mint::Event& e)
{
    m_cameraController.onEvent(e);
}

void Sandbox2D::onImGuiRender()
{
    MINT_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Sqaure Color", glm::value_ptr(m_color));
    ImGui::End();
}
