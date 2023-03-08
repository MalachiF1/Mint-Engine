#pragma once

#include <Mint.h>
#include <glm/glm.hpp>

class Sandbox2D final : public mint::Layer
{
  public:
    Sandbox2D();
    virtual ~Sandbox2D() override = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(mint::Timestep ts) override;
    virtual void onEvent(mint::Event& e) override;
    virtual void onImGuiRender() override;

  private:
    mint::OrthographicCameraController m_cameraController;

    // Temp
    mint::Ref<mint::VertexArray> m_vertexArray;
    mint::Ref<mint::Shader>      m_shader;
    mint::Ref<mint::Texture2D>   m_checkerboardTexture;
    mint::Ref<mint::Texture2D>   m_spriteSheet;
    glm::vec4                    m_color = {0.5f, 0.5f, 0.8f, 1.0f};
};
