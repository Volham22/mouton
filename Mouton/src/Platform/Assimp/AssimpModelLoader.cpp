#include "AssimpModelLoader.h"

#include <assimp/Importer.hpp>

namespace Mouton
{

    AssimpModelLoader::AssimpModelLoader(const std::string& path)
        : m_LoadedModel(), m_Path(path), m_Meshes(), m_Textures()
    {
    }

    bool AssimpModelLoader::Load()
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(m_Path,
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            MTN_ERROR("Scene {0} couldn't be loaded ! Reason: {1}", m_Path.c_str(),
                importer.GetErrorString());

            return false;
        }

        m_Path = m_Path.substr(0, m_Path.find_last_of('/')) + '/';
        LoadNodes(scene->mRootNode, scene);

        m_LoadedModel = std::make_shared<Model>(m_Meshes);

        return true;
    }

    std::shared_ptr<Model>& AssimpModelLoader::GetLoadedModel()
    {
        return m_LoadedModel;
    }

    void AssimpModelLoader::LoadNodes(aiNode* node, const aiScene* scene)
    {
        // Foreach meshes load it
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(LoadMesh(mesh, scene));
        }

        // Recursevely called for all of node's children
        for(unsigned int i = 0; i < node->mNumChildren; i++)
            LoadNodes(node->mChildren[i], scene);
    }

    Mesh AssimpModelLoader::LoadMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<MeshVertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshTexture> textures;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            MeshVertex vertex;

            vertex.positions.x = mesh->mVertices[i].x;
            vertex.positions.y = mesh->mVertices[i].y;
            vertex.positions.z = mesh->mVertices[i].z;

            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;

            if(mesh->mTextureCoords[0])
            {
                vertex.textureCoords.x = mesh->mTextureCoords[0][i].x;
                vertex.textureCoords.y = mesh->mTextureCoords[0][i].y;
            }
            else
                vertex.textureCoords = { 0.0, 0.0 };

            vertices.push_back(vertex);
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace& face = mesh->mFaces[i];

            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

            auto texDiff = LoadTextures(mat, aiTextureType_DIFFUSE, TextureType::Diffuse);
            auto texSpec = LoadTextures(mat, aiTextureType_SPECULAR, TextureType::Specular);
            auto texNorm = LoadTextures(mat, aiTextureType_HEIGHT, TextureType::Normal);
            auto texHei  = LoadTextures(mat, aiTextureType_AMBIENT, TextureType::Height);

            textures.insert(textures.end(), texDiff.begin(), texDiff.end());
            textures.insert(textures.end(), texSpec.begin(), texSpec.end());
            textures.insert(textures.end(), texNorm.begin(), texNorm.end());
            textures.insert(textures.end(), texHei.begin(),  texHei.end());
        }
        else
            MTN_WARN("Non textured models are not implemented yet");

        return Mesh(vertices, indices, textures);
    }

    std::vector<MeshTexture> AssimpModelLoader::LoadTextures(aiMaterial* mat, aiTextureType aiType, TextureType type)
    {
        std::vector<MeshTexture> textures;

        for(unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
        {
            aiString path;
            mat->GetTexture(aiType, i, &path);

            auto texKey = m_Textures.find(path.C_Str());

            if(texKey == m_Textures.end())
            {
                auto tex = Texture2D::CreateTexture((m_Path + path.C_Str()).c_str());

                m_Textures[path.C_Str()] = 
                    std::make_pair(type, tex);
                textures.push_back(std::make_pair(type, tex));
            }
            else
                textures.push_back(m_Textures[path.C_Str()]);
        }

        return textures;
    }


} // namespace Mouton
