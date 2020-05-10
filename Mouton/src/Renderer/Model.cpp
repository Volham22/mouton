#include "Model.h"

#include "Platform/Assimp/AssimpModelLoader.h"
#include "Renderer.h"

namespace Mouton
{

    std::unique_ptr<ModelLoader> ModelLoader::CreateModelLoader(const std::string& path)
    {
        // Only assimp is supported for now
        return std::make_unique<AssimpModelLoader>(path);
    }

    Model::Model(const std::vector<Mesh>& meshes)
        : m_Meshes(meshes), m_VAO(VertexArray::CreateVertexArray())
    {
        m_VAO->AddVertexBuffer(*(m_Meshes[0].m_VBO));
    }

        Model::Model(const std::vector<Mesh>& meshes, const std::unordered_map<std::string, Bone>& bones)
        : m_Meshes(meshes), m_Bones(bones), m_VAO(VertexArray::CreateVertexArray())
    {
        m_VAO->AddVertexBuffer(*(m_Meshes[0].m_VBO));
    }

    void Model::DrawModel()
    {
        m_VAO->Bind();

        for(Mesh& mesh : m_Meshes)
        {
            mesh.Bind();
            Renderer::DrawIndexed(mesh.m_EBO->GetCount());
            mesh.Unbind();
        }

        m_VAO->Unbind();
    }

} // namespace Mouton
