#ifndef MOUTON_CAMERA_H
#define MOUTON_CAMERA_H

#include "MoutonPch.h"

namespace Mouton
{

    class Camera
    {
    public:
        virtual void SetPosition(const glm::vec3& position) = 0;
        virtual void SetRotation(float rotation) = 0;
        virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
    };

    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float left, float right, float top, float bottom);
        virtual void SetPosition(const glm::vec3& position) override;
        virtual void SetRotation(float rotation) override;
        virtual const glm::mat4& GetViewProjectionMatrix() const override { return m_VP; };

    private:
        glm::mat4 m_Position, m_Rotation;
        glm::mat4 m_Proj, m_View;
        glm::mat4 m_VP;
    };

} // namespace Mouton

#endif //MOUTON_CAMERA_H
