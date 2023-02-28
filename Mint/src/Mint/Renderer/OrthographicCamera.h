#pragma once

#include <glm/glm.hpp>

namespace mint
{

    class OrthographicCamera
    {
      public:
        OrthographicCamera(
            float left,
            float right,
            float bottom,
            float top,
            float camNear  = -1.0f,
            float camFar   = 1.0f,
            float rotation = 0.0f,
            glm::vec3 pos  = glm::vec3(0.0f, 0.0f, 0.0f)
        );

        inline const glm::vec3& getPosition() const { return m_position; }
        inline float getRotation() const { return m_rotation; }

        inline const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
        inline const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
        inline const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

        inline void setPosition(const glm::vec3& position)
        {
            m_position = position;
            recalculateViewMatrix();
        }
        inline void setRotation(float rotation)
        {
            m_rotation = rotation;
            recalculateViewMatrix();
        }

      private:
        void recalculateViewMatrix();

      private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        // cache view * projection so we don't have to recalculate it a lot.
        glm::mat4 m_viewProjectionMatrix;

        glm::vec3 m_position;
        float m_rotation;
    };

} // namespace mint
