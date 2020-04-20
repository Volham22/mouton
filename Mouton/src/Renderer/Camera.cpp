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

}