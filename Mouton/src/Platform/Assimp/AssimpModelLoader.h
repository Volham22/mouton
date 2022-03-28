#ifndef ASSIMP_MODEL_LOADER_H
#define ASSIMP_MODEL_LOADER_H

#include "MoutonPch.h"

#include "Renderer/Model.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace Mouton {

    class AssimpModelLoader : public ModelLoader
    {
      public:
        AssimpModelLoader(const std::string& path);
        virtual bool Load() override;
        virtual std::shared_ptr<Model>& GetLoadedModel() override;
        virtual std::shared_ptr<std::vector<Animation>>&
        GetModelAnimations() override;

      private:
        void LoadNodes(aiNode* node, const aiScene* scene,
                       std::shared_ptr<Node>& currentNode);
        Mesh LoadMesh(aiMesh* mesh, const aiScene* scene, aiNode* meshNode,
                      std::shared_ptr<Node>& node);
        glm::mat4 ToGlmMat4(const aiMatrix4x4& matrix);
        void LoadMeshBones(aiMesh* mesh, aiNode* meshNode, const aiScene* scene,
                           std::vector<MeshVertex>& vertices,
                           std::shared_ptr<Node>& node);
        void LoadBoneKeyFrame(const aiScene* scene);
        std::vector<MeshTexture>
        LoadTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);

        std::shared_ptr<Model> m_LoadedModel;
        std::shared_ptr<std::vector<Animation>> m_Animations;
        std::string m_Path;
        int m_BonesIndex;
        std::unordered_map<std::string, std::shared_ptr<Bone>> m_Bones;
        std::unordered_map<std::string, aiNode*> m_BoneNode;
        std::unordered_map<std::string, MeshTexture> m_Textures;
    };

} // namespace Mouton

#endif