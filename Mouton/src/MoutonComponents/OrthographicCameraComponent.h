#ifndef ORTHOGRAPHIC_CAMERA_COMPONENT_H
#define ORTHOGRAPHIC_CAMERA_COMPONENT_H

#include "MoutonPch.h"

#include "Ecs/Components.h"
#include "Renderer/OrthographicCameraController.h"

namespace Mouton
{

    class OrthographicCameraComponent : public Component
    {
    public:
        OrthographicCameraComponent(const std::string& name,
            const std::shared_ptr<OrthographicCameraController>& controller);
        OrthographicCameraComponent() = delete;

        glm::vec3& GetPosition() { return m_CameraController->GetPosition(); }
        float& GetRotation() { return m_CameraController->GetRotation(); }

        void Move(const glm::vec3& movePosition);
        void Rotate(float angle);
        void SetCoords(float left, float right, float top, float bottom,
                float near=-1.0f, float far=1.0f);

    private:
        std::shared_ptr<OrthographicCameraController> m_CameraController;
    };

} // namespace Mouton


#endif
