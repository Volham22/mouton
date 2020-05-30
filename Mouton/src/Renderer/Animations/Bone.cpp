#include "Bone.h"

namespace Mouton
{

    Bone::Bone()
        : m_Index(0), m_Name(), m_AnimatedTransform(1.0f),
          m_LocalOffset(1.0f), m_GlobalTransform(1.0f), m_LocalTransform(1.0f)
    {
    }

    Bone::Bone(int index, const std::string& name, const glm::mat4& localTansform)
        : m_Index(index), m_Name(name), m_AnimatedTransform(1.0f),
          m_LocalOffset(localTansform), m_GlobalTransform(1.0f), m_LocalTransform(1.0f)
    {
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

    glm::mat4 Bone::Update(double animationProgress, const std::string& animationName, const glm::mat4& parentTransform)
    {
        int index = FindKeyFrame(animationProgress, animationName);

        if(index >= 0)
        {
            auto& keyFrameLow = m_KeyFrames[animationName][FindKeyFrame(animationProgress, animationName)];
            auto& keyFrameUp = m_KeyFrames[animationName][FindKeyFrame(animationProgress, animationName) + 1];

            glm::vec3 position = glm::mix(keyFrameLow.GetPosition(), keyFrameUp.GetPosition(), 
                static_cast<float>(animationProgress));
            glm::vec3 scale = glm::mix(keyFrameLow.GetScale(), keyFrameUp.GetScale(),
                static_cast<float>(animationProgress));
            glm::quat rotations = glm::slerp(keyFrameLow.GetRotation(), keyFrameUp.GetRotation(),
                static_cast<float>(animationProgress));

            m_LocalTransform = (glm::translate(glm::mat4(1.0f), position) *
                glm::mat4_cast(rotations) * glm::scale(glm::mat4(1.0f), scale));
            
            m_AnimatedTransform = m_LocalTransform * parentTransform * GetGlobalTransformInverse();

            return parentTransform;
        }

        return parentTransform;
    }

    int Bone::FindKeyFrame(double animProgress, const std::string& animationName)
    {
        auto& keyframes = m_KeyFrames[animationName];

        if(keyframes.size() == 0)
        {
            MTN_TRACE("At least 2 to keys are needed to interpolate !");
            return -1;
        }

        for(unsigned int i = 0; i < keyframes.size() - 1; i++)
        {
            if(keyframes[i + 1].GetTime() > animProgress)
                return i;
        }

        MTN_ERROR("Unable to find keyframe to interpolate !!");
        return -1;
    }

} // namespace Mouton
