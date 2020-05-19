#ifndef ASSIMP_MODEL_LOADER_H
#define ASSIMP_MODEL_LOADER_H

#include "MoutonPch.h"

#include "Renderer/Model.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Mouton
{

    class AssimpModelLoader : public ModelLoader
    {
    public:
        AssimpModelLoader(const std::string& path);
        virtual bool Load() override;
        virtual std::shared_ptr<Model>& GetLoadedModel() override;
        virtual std::shared_ptr<std::vector<Animation>>& GetModelAnimations() override;

    private:
        void LoadNodes(aiNode* node, const aiScene* scene);
        Mesh LoadMesh(aiMesh* mesh, const aiScene* scene, aiNode* meshNode);
        glm::mat4 ToGlmMat4(const aiMatrix4x4& matrix);
        void LoadMeshBones(aiMesh* mesh, std::vector<MeshVertex>& vertices, aiNode* meshNode, const aiScene* scene);
        void MakeChild(const aiScene* scene);
        void LoadBoneKeyFrame(const aiScene* scene);
        std::vector<MeshTexture> LoadTextures(aiMaterial* mat, aiTextureType aiType, TextureType type);

        std::shared_ptr<Model> m_LoadedModel;
        std::shared_ptr<std::vector<Animation>> m_Animations;
        std::string m_Path;
        std::vector<Mesh> m_Meshes;
        int m_BonesIndex;
        std::unordered_map<std::string, Bone> m_Bones;
        std::unordered_map<std::string, aiNode*> m_BoneNode;
        std::unordered_map<std::string, MeshTexture> m_Textures;
    };

} // namespace Mouton


#endif