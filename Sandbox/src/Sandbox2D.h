#pragma once

#include <Mint.h>
#include <glm/glm.hpp>

class Sandbox2D : public mint::Layer
{
  public:
    Sandbox2D();
    virtual ~Sandbox2D() override final = default;

    virtual void onAttach() override final;
    virtual void onDetach() override final;

    virtual void onUpdate(mint::Timestep ts) override final;
    virtual void onEvent(mint::Event& e) override final;
    virtual void onImGuiRender() override final;

  private:
    mint::OrthographicCameraController m_cameraController;

    // Temp
    mint::Ref<mint::VertexArray> m_vertexArray;
    mint::Ref<mint::Shader> m_shader;
    mint::Ref<mint::Texture2D> m_checkerboardTexture;
    glm::vec4 m_color = { 0.5f, 0.5f, 0.8f, 1.0f };
};
