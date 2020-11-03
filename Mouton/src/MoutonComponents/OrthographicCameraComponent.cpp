#include "OrthographicCameraComponent.h"

namespace Mouton
{

    OrthographicCameraComponent::OrthographicCameraComponent(const std::string& name,
        const std::shared_ptr<OrthographicCameraController>& controller)
        : Component(ComponentType::OrthographicCamera, name), cameraController(controller)
    {
    }

} // namespace Mouton
