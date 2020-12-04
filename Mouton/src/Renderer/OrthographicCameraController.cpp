#include "OrthographicCameraController.h"

namespace Mouton
{

    OrthographicCameraController::OrthographicCameraController(std::shared_ptr<OrthographicCamera> camera)
        : m_Camera(camera), m_Position(0.0f), m_Rotation(0.0f)
    {
    }

    void OrthographicCameraController::Move(const glm::vec3& movePosition)
    {
        m_Position += movePosition;
        m_Camera->SetPosition(m_Position);
    }

    void OrthographicCameraController::Translate(const glm::vec3& position)
    {
        m_Position = position;
        m_Camera->SetPosition(m_Position);
    }

    void OrthographicCameraController::Rotate(float angle)
    {
        m_Rotation += angle;
        m_Camera->SetRotation(m_Rotation); // Conversion in radians done by OrthographicCamera
    }

    void OrthographicCameraController::SetCoords(float left, float right, float top,
        float bottom, float near, float far)
    {
        m_Camera->SetCoords(left, right, top, bottom, near, far);
    }

} // namespace Mouton
