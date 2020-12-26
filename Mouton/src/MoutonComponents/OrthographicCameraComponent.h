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
            OrthographicCameraController* controller);
        OrthographicCameraComponent() = delete;

        ~OrthographicCameraComponent();

        glm::vec3& GetPosition() { return m_CameraController->GetPosition(); }
        float& GetRotation() { return m_CameraController->GetRotation(); }
        auto GetCameraControllerInstance() { return m_CameraController; }

        void Move(const glm::vec3& movePosition);
        void Translate(const glm::vec3& position);
        void Rotate(float angle);
        void SetCoords(float left, float right, float top, float bottom,
                float near=-1.0f, float far=1.0f);

        template<typename Writer>
        void Serialize(Writer& writer) const
        {
            writer.String("Position");
            writer.StartArray();
            writer.Double(static_cast<double>(m_CameraController->GetPosition().x));
            writer.Double(static_cast<double>(m_CameraController->GetPosition().y));
            writer.Double(static_cast<double>(m_CameraController->GetPosition().z));
            writer.EndArray();

            writer.String("Rotation");
            writer.Double(static_cast<double>(m_CameraController->GetRotation()));
        }

    private:
        OrthographicCameraController* m_CameraController;
    };

} // namespace Mouton


#endif
