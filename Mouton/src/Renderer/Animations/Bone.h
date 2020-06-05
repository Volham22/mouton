#ifndef BONE_H
#define BONE_H

#include "MoutonPch.h"

#include "KeyFrame.h"

// Maximum bones count allowed by shaders
#define MTN_MAX_BONES_COUNT 30

namespace Mouton
{

    class Bone
    {
    public:
        Bone();
        Bone(int index, const std::string& name, const glm::mat4& localTansform);
        void AddKeyFrame(const std::string& animationName, const KeyFrame& keyFrame);
        void SortKeyFrames();
        void SetGlobalTransformMatrix(const glm::mat4& matrix) { m_GlobalTransform = matrix; };
        int GetIndex() const { return m_Index; };
        glm::mat4 GetAnimatedTransform() const { return m_AnimatedTransform; };
        void SetLocalOffset(const glm::mat4& offsetMatrix) { m_LocalOffset = offsetMatrix; };
        glm::mat4 GetGlobalTransformInverse() const { return glm::inverse(m_GlobalTransform); };
        glm::mat4 Update(double animationProgress, const std::string& animationName, const glm::mat4& parentTransform);
    private:
        int m_Index;
        std::string m_Name;
        std::unordered_map<std::string, std::vector<KeyFrame>> m_KeyFrames;
        glm::mat4 m_AnimatedTransform;
        glm::mat4 m_LocalOffset;
        glm::mat4 m_GlobalTransform;
        glm::mat4 m_LocalTransform;

        int FindKeyFrame(double animationProgress, const std::string& animationName);
    };


} // namespace Mouton


#endif