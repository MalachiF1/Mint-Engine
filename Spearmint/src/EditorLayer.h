#pragma once

#include <Mint.h>
#include <glm/glm.hpp>

namespace mint
{

class EditorLayer final : public Layer
{
  public:
    EditorLayer();
    virtual ~EditorLayer() override = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(Timestep ts) override;
    virtual void onEvent(Event& e) override;
    virtual void onImGuiRender() override;

  private:
    OrthographicCameraController m_cameraController;

    // Temp
    bool m_viewportFocused = false;
    bool m_viewportHovered = false;
    Ref<Texture2D> m_checkerboardTexture;
    Ref<Texture2D> m_spriteSheet;
    Ref<Framebuffer> m_framebuffer;
    glm::vec2 m_viewportSize = {0.0f, 0.0f};
    glm::vec4 m_color        = {0.5f, 0.5f, 0.8f, 1.0f};
};

} // namespace mint
