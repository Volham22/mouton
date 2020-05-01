#include "Scene.h"

#include "Platform/Assimp/AssimpSceneLoader.h"
#include "Renderer.h"

namespace Mouton
{

    std::unique_ptr<SceneLoader> SceneLoader::CreateSceneLoader(const std::string& path)
    {
        // Only assimp is supported for now
        return std::make_unique<AssimpSceneLoader>(path);
    }

    Scene::Scene(const std::vector<Mesh>& meshes)
        : m_Meshes(meshes), m_VAO(VertexArray::CreateVertexArray())
    {
        m_VAO->AddVertexBuffer(*(m_Meshes[0].m_VBO));
    }

    void Scene::DrawScene()
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
