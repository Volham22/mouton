#ifndef KEYFRAME_H
#define KEYFRAME_H

#include "MoutonPch.h"

namespace Mouton
{

    class KeyFrame
    {
    public:
        KeyFrame();
        KeyFrame(const std::string& name, const glm::vec3& pos,
            const glm::vec3 &scale, const glm::quat& rotation, double time);
        const std::string& GetName() const { return m_Name; };
        const glm::vec3& GetPosition() const { return m_Position; };
        const glm::vec3& GetScale() const { return m_Scale; };
        const glm::quat& GetRotation() const { return m_Rotation; };

        bool operator<(const KeyFrame& other) const;

    private:
        std::string m_Name;
        glm::vec3 m_Position, m_Scale;
        glm::quat m_Rotation;
        double m_Time;
    };

} // namespace Mouton


#endif