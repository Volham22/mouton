#include "AssimpModelLoader.h"

#include <assimp/Importer.hpp>

namespace Mouton
{

    AssimpModelLoader::AssimpModelLoader(const std::string& path)
        : m_LoadedModel(), m_Animations(new std::vector<Animation>()), m_Path(path),
          m_BonesIndex(0), m_Bones(), m_BoneNode(), m_Textures()
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
        auto rootNode = std::make_shared<Node>(ToGlmMat4(scene->mRootNode->mTransformation));
        LoadNodes(scene->mRootNode, scene, rootNode);
        LoadBoneKeyFrame(scene);

        m_LoadedModel = m_Bones.size() > 0 ?
            std::make_shared<Model>(m_Animations, rootNode) :
            std::make_shared<Model>(rootNode);

        return true;
    }

    std::shared_ptr<Model>& AssimpModelLoader::GetLoadedModel()
    {
        return m_LoadedModel;
    }

    std::shared_ptr<std::vector<Animation>>& AssimpModelLoader::GetModelAnimations()
    {
        return m_Animations;
    }

    void AssimpModelLoader::LoadNodes(aiNode* node, const aiScene* scene, std::shared_ptr<Node>& currentNode)
    {
        // Foreach meshes load it
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            currentNode->AddMesh(LoadMesh(mesh, scene, node, currentNode));
        }

        // Recursevely called for all of node's children
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            auto child = std::make_shared<Node>(ToGlmMat4(node->mTransformation));
            currentNode->AddChildren(child);
            LoadNodes(node->mChildren[i], scene, child);
        }
    }

    Mesh AssimpModelLoader::LoadMesh(aiMesh* mesh, const aiScene* scene, aiNode* meshNode, std::shared_ptr<Node>& node)
    {
        std::vector<MeshVertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshTexture> textures;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            MeshVertex vertex;

            // Make the ID to -1 by default, it is required for weight assignment by LoadMeshBones
            vertex.bonesID = glm::ivec4(-1);
            vertex.weight = glm::vec4(0.0f);

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

        LoadMeshBones(mesh, meshNode, scene, vertices, node); // Load mesh bones if any

        return Mesh(vertices, indices, textures, mesh->mNumBones > 0 ? true : false);
    }

    glm::mat4 AssimpModelLoader::ToGlmMat4(const aiMatrix4x4& m)
    {
        glm::mat4 res;

        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
                res[i][j] = m[i][j];
        }

        return res;
    }

    void AssimpModelLoader::LoadMeshBones(aiMesh* mesh, aiNode* meshNode,
        const aiScene* scene, std::vector<MeshVertex>& vertices, std::shared_ptr<Node>& node)
    {
        for(int i = 0; i < mesh->mNumBones; i++)
        {
            std::string boneName = mesh->mBones[i]->mName.C_Str();
            auto it = m_Bones.find(boneName);
            aiBone* bone = mesh->mBones[i];

            if(it == m_Bones.end())
            {
                auto meshBone = std::make_shared<Bone>(++m_BonesIndex, boneName, ToGlmMat4(bone->mOffsetMatrix));
                meshBone->SetGlobalTransformMatrix(ToGlmMat4(scene->mRootNode->mTransformation));
                m_Bones[boneName] = meshBone;
                m_BoneNode[boneName] = meshNode;
                node->AddBone(meshBone);
            }
            else
                node->AddBone(m_Bones[boneName]);

            // Add vertex weight
            for(int j = 0; j < bone->mNumWeights; j++)
            {
                int vertexID = bone->mWeights[j].mVertexId;
                int bonePos = 0;

                // We support only 4 bones to affect a vertex, if it's more than 4 then it will be undefined
                // behaviour. A warning may be emmitted
                while(bonePos < 4 && vertices[vertexID].bonesID[bonePos] != -1)
                    bonePos++;

                if(bonePos < 4)
                {
                    vertices[vertexID].bonesID[bonePos] = m_Bones[boneName]->GetIndex();
                    vertices[vertexID].weight[bonePos]  = bone->mWeights[j].mWeight;
                }
                else
                    MTN_WARN("Bone {0} affect more than 4 vertices !", boneName.c_str()); // TODO: Take the most relevant one
            }
        }
    }

    void AssimpModelLoader::LoadBoneKeyFrame(const aiScene* scene)
    {
        if(scene->mNumAnimations > 0)
        {
            for(int i = 0; i < scene->mNumAnimations; i++)
            {
                aiAnimation* animation = scene->mAnimations[i];
                std::string animName = animation->mName.C_Str();

                m_Animations->push_back(Animation(animName, animation->mDuration, animation->mTicksPerSecond));

                for(int j  = 0; j < animation->mNumChannels; j++)
                {
                    KeyFrame key;
                    for(int k = 0; k < animation->mChannels[j]->mNumPositionKeys; k++)
                    {
                        aiNode* animNode = scene->mRootNode->FindNode(animation->mChannels[j]->mNodeName);

                        glm::vec3 position;
                        position.x = animation->mChannels[j]->mPositionKeys[k].mValue.x;
                        position.y = animation->mChannels[j]->mPositionKeys[k].mValue.y;
                        position.z = animation->mChannels[j]->mPositionKeys[k].mValue.z;

                        glm::vec3 scale;
                        scale.x = animation->mChannels[j]->mScalingKeys[k].mValue.x;
                        scale.y = animation->mChannels[j]->mScalingKeys[k].mValue.y;
                        scale.z = animation->mChannels[j]->mScalingKeys[k].mValue.z;

                        glm::quat rotation;
                        rotation.x = animation->mChannels[j]->mRotationKeys[k].mValue.x;
                        rotation.y = animation->mChannels[j]->mRotationKeys[k].mValue.y;
                        rotation.z = animation->mChannels[j]->mRotationKeys[k].mValue.z;
                        rotation.w = animation->mChannels[j]->mRotationKeys[k].mValue.w;

                        double time = animation->mChannels[j]->mPositionKeys[k].mTime;

                        key = KeyFrame(animName, position, scale, rotation, time);

                        auto it = m_Bones.find(animNode->mName.C_Str());
                        if(it != m_Bones.end())
                            m_Bones[animNode->mName.C_Str()]->AddKeyFrame(animName, key);

                    }
                }
            }
        }
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
