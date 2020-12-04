#include "OrthographicCameraComponent.h"

namespace Mouton
{

    OrthographicCameraComponent::OrthographicCameraComponent(const std::string& name,
        OrthographicCameraController* controller)
        : Component(ComponentType::OrthographicCamera, name, true), m_CameraController(controller)
    {
    }

    void OrthographicCameraComponent::Move(const glm::vec3& movePosition)
    {
        m_CameraController->Move(movePosition);
    }

    void OrthographicCameraComponent::Translate(const glm::vec3& position)
    {
        m_CameraController->Translate(position);
    }

    void OrthographicCameraComponent::Rotate(float angle)
    {
        m_CameraController->Rotate(angle);
    }

    void OrthographicCameraComponent::SetCoords(float left, float right,
            float top, float bottom, float near, float far)
    {
        m_CameraController->SetCoords(left, right, top, bottom, near, far);
    }

    OrthographicCameraComponent::~OrthographicCameraComponent()
    {
        delete m_CameraController;
    }

} // namespace Mouton
