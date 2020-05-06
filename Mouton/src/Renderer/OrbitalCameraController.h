#ifndef ORBITAL_CAMERA_CONTROLLER_H
#define ORBITAL_CAMERA_CONTROLLER_H

#include "Camera.h"

namespace Mouton
{

    class OrbitalCameraController
    {
    public:
        OrbitalCameraController(const std::shared_ptr<OrbitalCamera>& cam, float cameraSpeed = 0.5f);
        OrbitalCameraController(float cameraSpeed = 0.5f);

        void Control(const std::shared_ptr<OrbitalCamera>& cam) { m_Camera = cam; };
        bool OnEvent(Event& event);
        const glm::mat4& GetViewProjectionMatrix() const { return m_Camera->GetViewProjectionMatrix(); };
    
    private:
        std::shared_ptr<OrbitalCamera> m_Camera;
        float m_HorizontalAngle, m_VerticalAngle, m_Distance, m_CameraSpeed;
        glm::vec2 m_LastMousePosition;
    };

} // namespace Mouton


#endif