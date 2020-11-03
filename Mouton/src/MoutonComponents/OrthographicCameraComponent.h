#ifndef ORTHOGRAPHIC_CAMERA_COMPONENT_H
#define ORTHOGRAPHIC_CAMERA_COMPONENT_H

#include "MoutonPch.h"

#include "Ecs/Components.h"
#include "Renderer/OrthographicCameraController.h"

namespace Mouton
{

    struct OrthographicCameraComponent : public Component {
        std::shared_ptr<OrthographicCameraController> cameraController;

        OrthographicCameraComponent(const std::string& name,
            const std::shared_ptr<OrthographicCameraController>& controller);
        OrthographicCameraComponent() = delete;
    };

} // namespace Mouton


#endif
