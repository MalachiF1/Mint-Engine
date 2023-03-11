#include "EditorLayer.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <memory>

namespace mint
{


EditorLayer::EditorLayer() : Layer("EditorLayer"), m_cameraController(1200.0f / 720.0f, true)
{
    MINT_PROFILE_FUNCTION();

    FramebufferSpecification spec;
    auto [width, height] = Application::get().getWindow().getSize();
    spec.width           = width;
    spec.height          = height;
    m_framebuffer        = Framebuffer::create(spec);

    m_checkerboardTexture = Texture2D::create("assets/textures/Checkerboard.png");
    m_spriteSheet         = Texture2D::create("assets/textures/kenney_tinydungeon/tilemap/tilemap_packed.png");
}

void EditorLayer::onAttach()
{
    MINT_PROFILE_FUNCTION();
}

void EditorLayer::onDetach()
{
    MINT_PROFILE_FUNCTION();
}

void EditorLayer::onUpdate(Timestep ts)
{
    MINT_PROFILE_FUNCTION();

    if (m_viewportFocused)
        m_cameraController.onUpdate(ts);

    {
        MINT_PROFILE_SCOPE("Renderer Prep");
        m_framebuffer->bind();
        RenderCommand::setClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        RenderCommand::clear();
    }

    {
        MINT_PROFILE_SCOPE("Renderer Draw");
        static float rotation = 0.0f;
        rotation += ts * 40.0f;

        Ref<SubTexture2D> darkWizard = SubTexture2D::createFromCoords(m_spriteSheet, {3.0f, 1.0f}, {16.0f, 16.0f});
        Ref<SubTexture2D> mimic = SubTexture2D::createFromCoords(m_spriteSheet, {7.0f, 3.0f}, {16.0f, 16.0f}, {2.0f, 1.0f});

        Renderer2D::beginScene(m_cameraController.getCamera());
        Renderer2D::drawQuad({0.0f, 0.5f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
        Renderer2D::drawQuad({0.0f, 0.0f, -0.1f}, {8.0f, 8.0f}, m_checkerboardTexture, 10.0f, {1.0f, 1.0f, 0.8f, 1.0f});
        Renderer2D::drawRotatedQuad(
            {-0.5f, -0.5f, 0.2}, {1.0f, 1.0f}, rotation, m_checkerboardTexture, 20.0f, {8.0f, 1.0f, 1.0f, 1.0f}
        );
        Renderer2D::drawQuad({0.3f, 0.3f, 0.1f}, {0.9f, 0.3f}, m_color);
        Renderer2D::drawRotatedQuad({0.9f, 0.1f, 0.3f}, {3.0f, 0.5f}, 45.0f, m_color);
        Renderer2D::drawQuad({0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, darkWizard, 1, {1.0f, 1.0f, 1.0f, 0.5});
        Renderer2D::drawQuad({1.5f, 0.0f, 1.0f}, {0.7f * 2, 0.7f}, mimic, 1, {1.0f, 1.0f, 1.0f, 0.5});
        Renderer2D::endScene();
        m_framebuffer->unbind();
    }
}

void EditorLayer::onEvent(Event& e)
{
    m_cameraController.onEvent(e);
}

void EditorLayer::onImGuiRender()
{
    MINT_PROFILE_FUNCTION();

    static bool dockspaceOpen = true;

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
                  | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.


    ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);

    // Submit the DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        MINT_ASSERT(false, "Dockspace should always be enabled");
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
                Application::get().shutdown();

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Sqaure Color", glm::value_ptr(m_color));
    ImGui::End();

    ImGui::Begin("Viewport");
    m_viewportFocused = ImGui::IsWindowFocused();
    m_viewportHovered = ImGui::IsWindowHovered();
    Application::get().getImGuiLayer()->setBlockEvents(!m_viewportFocused || !m_viewportHovered);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (m_viewportSize.x != viewportPanelSize.x || m_viewportSize.y != viewportPanelSize.y)
    {
        m_framebuffer->resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
        m_cameraController.resizeBounds(viewportPanelSize.x, viewportPanelSize.y);
        m_viewportSize = {viewportPanelSize.x, viewportPanelSize.y};
    }

    uint32_t textureID = m_framebuffer->getColorAttachmentRendererID();
    ImGui::Image((void*)textureID, ImVec2(m_viewportSize.x, m_viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);
    ImGui::End();
}

} // namespace mint
