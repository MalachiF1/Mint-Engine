#include "mtpch.h"

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace mint
{

    OrthographicCamera::OrthographicCamera(
        float left, float right, float bottom, float top, float camNear, float camFar, float rotation, glm::vec3 pos
    ) :
        m_projectionMatrix(glm::ortho(left, right, bottom, top, camNear, camFar)),
        m_viewMatrix(glm::mat4(1.0f)), m_viewProjectionMatrix(m_projectionMatrix * m_viewMatrix), m_position(pos),
        m_rotation(rotation)
    {
        MINT_PROFILE_FUNCTION();
    }

    void OrthographicCamera::setProjection(
        float left, float right, float bottom, float top, float camNear, float camFar
    )
    {
        MINT_PROFILE_FUNCTION();

        m_projectionMatrix     = glm::ortho(left, right, bottom, top, camNear, camFar);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::recalculateViewMatrix()
    {
        MINT_PROFILE_FUNCTION();

        glm::mat4 transform = (glm::translate(glm::mat4(1.0f), m_position));

        transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

        m_viewMatrix           = glm::inverse(transform);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }


} // namespace mint
