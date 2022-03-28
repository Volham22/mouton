#include "KeyFrame.h"

namespace Mouton {

    KeyFrame::KeyFrame()
        : m_Name(), m_Position(0.0f), m_Scale(0.0f), m_Rotation(), m_Time(0.0)
    {}

    KeyFrame::KeyFrame(const std::string& name, const glm::vec3& pos,
                       const glm::vec3& scale, const glm::quat& rotation,
                       double time)
        : m_Name(name), m_Position(pos), m_Scale(scale), m_Rotation(rotation),
          m_Time(time)
    {}

    bool KeyFrame::operator<(const KeyFrame& other) const
    {
        return m_Time < other.m_Time;
    }

} // namespace Mouton
