#ifndef NODE_H
#define NODE_H

#include "Animations/Bone.h"
#include "Mesh.h"
#include "MoutonPch.h"

namespace Mouton {

    class Node
    {
      public:
        Node();
        Node(const glm::mat4& transform);
        Node(const std::vector<Mesh>& meshes,
             const std::vector<std::shared_ptr<Bone>>& bones,
             const glm::mat4& transform);
        void ProcessNodeHierarchy(const std::string& animationName,
                                  double animationProgress,
                                  glm::mat4 parentTransform);
        void AddMesh(const Mesh& mesh);
        void AddBone(const std::shared_ptr<Bone>& bone);
        void AddChildren(const std::shared_ptr<Node>& node);
        void RetrieveBonesTransform(
            std::shared_ptr<std::array<glm::mat4, MTN_MAX_BONES_COUNT>>&
                transforms);
        void Draw() const;
        glm::mat4 GetTransformation() const { return m_Transform; };

      private:
        std::vector<Mesh> m_Meshes;
        std::vector<std::shared_ptr<Bone>> m_Bones;
        std::vector<std::shared_ptr<Node>> m_Children;
        glm::mat4 m_Transform;
    };

} // namespace Mouton

#endif