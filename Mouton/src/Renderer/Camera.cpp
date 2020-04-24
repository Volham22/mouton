#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Mouton
{

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_Position(1.0f), m_Rotation(1.0f),
          m_Proj(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_View(1.0f), m_VP(1.0f)
    {
        m_VP = m_Proj * m_View;
    }

    void OrthographicCamera::SetPosition(const glm::vec3 &position)
    {
        m_Position = glm::translate(glm::mat4(1.0f), position);
        m_View = glm::inverse(m_Position * m_Rotation);
        m_VP = m_Proj * m_View;
    }

    void OrthographicCamera::SetRotation(float angle)
    {
        m_Rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
        m_View = glm::inverse(m_Position * m_Rotation);
        m_VP = m_Proj * m_View;
    }

    PerspectiveCamera::PerspectiveCamera(float aspectRatio, float fov, const glm::vec3& position, const glm::vec3& direction)
        : m_Position(position), m_Direction(direction), m_Projection(1.0f), m_VP(1.0f)
    {
        m_Projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
        m_VP = m_Projection * glm::lookAt(position, glm::normalize(m_Position - m_Direction), glm::vec3(0, 0, 1));
    }

    void PerspectiveCamera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        m_VP = m_Projection * glm::lookAt(m_Position, m_Direction, glm::vec3(0, 0, 1));
    }

    void PerspectiveCamera::SetDirection(const glm::vec3& direction)
    {
        m_Direction = glm::normalize(m_Position - direction);
        m_VP = m_Projection * glm::lookAt(m_Position, m_Direction, glm::vec3(0, 0, 1));
    }

}