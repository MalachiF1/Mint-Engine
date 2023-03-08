#pragma once

#include "Mint/Core/Timestep.h"
#include "Mint/Event/ApplicationEvent.h"
#include "Mint/Event/MouseEvent.h"
#include "Mint/Renderer/OrthographicCamera.h"

namespace mint
{

class OrthographicCameraController
{
  public:
    OrthographicCameraController(float aspectRatio, bool rotationEnabled = false);

    void onUpdate(Timestep ts);
    void onEvent(Event& e);

    inline OrthographicCamera&       getCamera() { return m_camera; }
    inline const OrthographicCamera& getCamera() const { return m_camera; }

  private:
    bool onMouseScrolled(MouseScrolledEvent& e);
    bool onWindowResized(WindowResizeEvent& e);

  private:
    float              m_aspectRatio;
    float              m_zoomLevel = 1.0f;
    OrthographicCamera m_camera;
    bool               m_rotationEnabled;
    float              m_cameraRotation         = 0.0f;
    glm::vec3          m_cameraPosition         = glm::vec3(0.0f);
    float              m_cameraTranslationSpeed = m_zoomLevel;
    float              m_cameraRotationSpeed    = 25.0f;
};

} // namespace mint
