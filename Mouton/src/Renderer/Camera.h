#ifndef MOUTON_CAMERA_H
#define MOUTON_CAMERA_H

#include "MoutonPch.h"

namespace Mouton
{

    class Camera
    {
    public:
        virtual void SetPosition(const glm::vec3& position) = 0;
        virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
    };

    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float left, float right, float top, float bottom);
        virtual void SetPosition(const glm::vec3& position) override;
        virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_VP; };
        void SetRotation(float rotation);

    private:
        glm::mat4 m_Position, m_Rotation;
        glm::mat4 m_Proj, m_View;
        glm::mat4 m_VP;
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float aspectRatio, float fov, const glm::vec3& position, const glm::vec3& direction);
        virtual void SetPosition(const glm::vec3& position) override;
        virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_VP; };
        // Set camera direction
        void SetDirection(const glm::vec3& direction);
    
    private:
        glm::vec3 m_Position, m_Direction;
        glm::mat4 m_Projection;
        glm::mat4 m_VP;
    };

} // namespace Mouton

#endif //MOUTON_CAMERA_H
