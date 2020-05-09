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
    
    private:
        void LoadNodes(aiNode* node, const aiScene* scene);
        Mesh LoadMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<MeshTexture> LoadTextures(aiMaterial*  mat, aiTextureType aiType, TextureType type);

        std::shared_ptr<Model> m_LoadedModel;
        std::string m_Path;
        std::vector<Mesh> m_Meshes;
        std::unordered_map<std::string, MeshTexture> m_Textures;
    };

} // namespace Mouton


#endif