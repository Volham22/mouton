#include "Bone.h"

namespace Mouton
{

    Bone::Bone()
        : m_Index(0), m_Name(), m_Childs(), m_LocalBindTransform(1.0f),
          m_AnimatedTransform(1.0f)
    {
    }

    Bone::Bone(int index, const std::string& name, const glm::mat4& localTansform)
        : m_Index(index), m_Name(name), m_Childs(), m_LocalBindTransform(m_LocalBindTransform),
          m_AnimatedTransform(1.0f)
    {
    }

    void Bone::AddChild(const Bone& child)
    {
        m_Childs.push_back(child);
    }

    void Bone::AddKeyFrame(const std::string& animationName, const KeyFrame& keyFrame)
    {
        m_KeyFrames[animationName].push_back(keyFrame);
    }

    void Bone::SortKeyFrames()
    {
        for(auto& [name, keyFrame] : m_KeyFrames)
            std::sort(keyFrame.begin(), keyFrame.end());
    }

} // namespace Mouton
