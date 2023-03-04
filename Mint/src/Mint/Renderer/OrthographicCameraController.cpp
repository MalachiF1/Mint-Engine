#include "mtpch.h"

#include "OrthographicCameraController.h"

#include "Mint/Core/Input.h"
#include "Mint/Core/KeyCodes.h"

namespace mint
{

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotationEnabled) :
        m_aspectRatio(aspectRatio),
        m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel),
        m_rotationEnabled(rotationEnabled)
    {
    }

    void OrthographicCameraController::onUpdate(Timestep ts)
    {
        MINT_PROFILE_FUNCTION();

        if (Input::isKeyPressed(MINT_KEY_W))
            m_cameraPosition.y += m_cameraTranslationSpeed * ts;

        if (Input::isKeyPressed(MINT_KEY_S))
            m_cameraPosition.y -= m_cameraTranslationSpeed * ts;

        if (Input::isKeyPressed(MINT_KEY_D))
            m_cameraPosition.x += m_cameraTranslationSpeed * ts;

        if (Input::isKeyPressed(MINT_KEY_A))
            m_cameraPosition.x -= m_cameraTranslationSpeed * ts;

        if (m_rotationEnabled)
        {
            if (Input::isKeyPressed(MINT_KEY_E))
                m_cameraRotation -= m_cameraRotationSpeed * ts;

            if (Input::isKeyPressed(MINT_KEY_Q))
                m_cameraRotation += m_cameraRotationSpeed * ts;

            m_camera.setRotation(m_cameraRotation);
        }

        m_camera.setPosition(m_cameraPosition);
        m_cameraTranslationSpeed = m_zoomLevel;
    }

    void OrthographicCameraController::onEvent(Event& e)
    {
        MINT_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(MINT_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(MINT_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
    }

    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
    {
        MINT_PROFILE_FUNCTION();

        m_zoomLevel -= e.getYOffset() * 0.25f;
        m_zoomLevel = std::max(m_zoomLevel, 0.25f);
        m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

        return false;
    }

    bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e)
    {
        MINT_PROFILE_FUNCTION();

        m_aspectRatio = (float)e.getWidth() / (float)e.getHeight();
        m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);

        return false;
    }

} // namespace mint