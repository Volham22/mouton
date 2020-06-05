#include "Node.h"

namespace Mouton
{

    Node::Node()
        : m_Meshes(), m_Bones(), m_Children(), m_Transform(1.0f)
    {
    }

    Node::Node(const glm::mat4& transform)
        : m_Meshes(), m_Bones(), m_Transform(transform)
    {
    }

    Node::Node(const std::vector<Mesh>& meshes, const std::vector<std::shared_ptr<Bone>>& bones, const glm::mat4& transform)
        : m_Meshes(meshes), m_Bones(bones), m_Transform(transform)
    {
    }

    void Node::ProcessNodeHierarchy(const std::string& animationName, double animationProgress, glm::mat4 parentTransform)
    {
        if(m_Bones.size() > 0)
        {
            for(auto& bone : m_Bones)
            {
                bone->Update(animationProgress, animationName, parentTransform);
            }
        }

        for(auto& child : m_Children)
            child->ProcessNodeHierarchy(animationName, animationProgress, parentTransform * m_Transform);
    }

    void Node::AddChildren(const std::shared_ptr<Node>& node)
    {
        m_Children.push_back(node);
    }

    void Node::AddBone(const std::shared_ptr<Bone>& bone)
    {
        m_Bones.push_back(bone);
    }

    void Node::AddMesh(const Mesh& mesh)
    {
        m_Meshes.push_back(mesh);
    }

    void Node::RetrieveBonesTransform(std::shared_ptr<std::array<glm::mat4, MTN_MAX_BONES_COUNT>>& transforms)
    {
        for(auto& bone : m_Bones)
            (*transforms)[bone->GetIndex()] = bone->GetAnimatedTransform();

        // Recursively call for transformations
        for(auto& child : m_Children)
            child->RetrieveBonesTransform(transforms);
    }

    void Node::Draw() const
    {
        std::for_each(m_Meshes.begin(), m_Meshes.end(), [](auto& mesh) { mesh.Draw(); });
        std::for_each(m_Children.begin(), m_Children.end(), [](auto& node) { node->Draw(); });
    }


} // namespace Mouton
