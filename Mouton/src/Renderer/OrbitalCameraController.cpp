#include "OrbitalCameraController.h"

#include "Core/Inputs.h"

namespace Mouton {

    OrbitalCameraController::OrbitalCameraController(
        const std::shared_ptr<OrbitalCamera>& cam, float cameraSpeed)
        : m_Camera(cam), m_HorizontalAngle(1.0f), m_VerticalAngle(1.0f),
          m_Distance(20.0f), m_CameraSpeed(cameraSpeed),
          m_LastMousePosition(1.0f)
    {}

    OrbitalCameraController::OrbitalCameraController(float cameraSpeed)
        : m_Camera(), m_HorizontalAngle(1.0f), m_VerticalAngle(1.0f),
          m_Distance(1.0f), m_CameraSpeed(cameraSpeed),
          m_LastMousePosition(1.0f)
    {}

    bool OrbitalCameraController::OnEvent(Event& event)
    {
        EventSystem::ApplyFunction<MouseMovedEvent>(
            &event, [this](Event& event) -> bool {
                MouseMovedEvent& ev = reinterpret_cast<MouseMovedEvent&>(event);

                if (Inputs::IsKeyPressed(Keys::MOUSE3))
                {
                    float deltaX = m_LastMousePosition.x - ev.GetXPosition();
                    m_HorizontalAngle += (deltaX * m_CameraSpeed);

                    float deltaY = m_LastMousePosition.y - ev.GetYPosition();
                    m_VerticalAngle += (deltaY * m_CameraSpeed);
                }

                m_LastMousePosition.x = ev.GetXPosition();
                m_LastMousePosition.y = ev.GetYPosition();

                return true;
            });

        EventSystem::ApplyFunction<MouseScrolledEvent>(
            &event, [this](Event& event) -> bool {
                MouseScrolledEvent& ev
                    = reinterpret_cast<MouseScrolledEvent&>(event);

                m_Distance += ev.GetYOffset();

                return true;
            });

        m_Camera->Orbit(m_HorizontalAngle, m_VerticalAngle, m_Distance);
        return event.Handled();
    }

} // namespace Mouton
