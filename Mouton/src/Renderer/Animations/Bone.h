#ifndef BONE_H
#define BONE_H

#include "MoutonPch.h"

#include "KeyFrame.h"

namespace Mouton
{

    class Bone
    {
    public:
        Bone();
        Bone(int index, const std::string& name, const glm::mat4& localTansform);
        void AddChild(const Bone& child);
        void AddKeyFrame(const std::string& animationName, const KeyFrame& keyFrame);
        void SortKeyFrames();
        int GetIndex() const { return m_Index; };
        glm::mat4 GetAnimatedTransform() const { return m_AnimatedTransform; };
        void SetAnimatedTransform(const glm::mat4& animatedTransform) { m_AnimatedTransform = animatedTransform; };
        glm::mat4 GetInverseBindTransform() const { return glm::inverse(m_LocalBindTransform); };
        // TODO calculate transform
    private:
        int m_Index;
        std::string m_Name;
        std::vector<Bone> m_Childs;
        std::unordered_map<std::string, std::vector<KeyFrame>> m_KeyFrames;
        glm::mat4 m_AnimatedTransform;
        glm::mat4 m_LocalBindTransform;
    };


} // namespace Mouton


#endif