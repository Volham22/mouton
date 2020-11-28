#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_H
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_H

#include "MoutonPch.h"

#include "Camera.h"

namespace Mouton
{

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController() = delete;
        OrthographicCameraController(std::shared_ptr<OrthographicCamera> camera);

        glm::vec3& GetPosition() { return m_Position; }
        float& GetRotation() { return m_Rotation; }
        auto GetCameraInstance() { return m_Camera; }

        void Move(const glm::vec3& movePosition);
        void Rotate(float angle);
        void SetCoords(float left, float right, float top, float bottom, float near=-1.0f, float far=1.0f);

    private:
        std::shared_ptr<OrthographicCamera> m_Camera;
        glm::vec3 m_Position;
        float m_Rotation;
    };

} // namespace Mouton


#endif
