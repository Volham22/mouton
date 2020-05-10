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
        void SetGlobalTransformMatrix(const glm::mat4& matrix) { m_GlobalTransform = matrix; };
        int GetIndex() const { return m_Index; };
        glm::mat4 GetAnimatedTransform() const { return m_AnimatedTransform; };
        void SetAnimatedTransform(const glm::mat4& animatedTransform) { m_AnimatedTransform = animatedTransform; };
        glm::mat4 GetGlobalTransformInverse() const { return glm::inverse(m_GlobalTransform); };
        void Update(double animationProgress, const std::string& animationName);
    private:
        int m_Index;
        std::string m_Name;
        std::vector<Bone> m_Childs;
        std::unordered_map<std::string, std::vector<KeyFrame>> m_KeyFrames;
        glm::mat4 m_AnimatedTransform;
        glm::mat4 m_LocalOffset;
        glm::mat4 m_GlobalTransform;

        void UpdateRec(double animationProgress, const std::string& animationName, const glm::mat4& parentTransform);
        int FindKeyFrame(double animationProgress, const std::string& animationName);
    };


} // namespace Mouton


#endif