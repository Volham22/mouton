#include "OrthographicCameraComponent.h"

namespace Mouton
{

    OrthographicCameraComponent::OrthographicCameraComponent(const std::string& name,
        const std::shared_ptr<OrthographicCameraController>& controller)
        : Component(ComponentType::OrthographicCamera, name), cameraController(controller)
    {
    }


    void OrthographicCameraComponent::Move(const glm::vec3& movePosition)
    {
        cameraController->Move(movePosition);
    }

    void OrthographicCameraComponent::Rotate(float angle)
    {
        cameraController->Rotate(angle);
    }

    void OrthographicCameraComponent::SetCoords(float left, float right,
            float top, float bottom, float near, float far)
    {
        cameraController->SetCoords(left, right, top, bottom, near, far);
    }

} // namespace Mouton
