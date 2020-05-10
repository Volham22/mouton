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

        Model::Model(const std::vector<Mesh>& meshes, const std::unordered_map<std::string, Bone>& bone,
            const std::shared_ptr<std::vector<Animation>>& animations, const std::string& rootNodeName)
        : m_Meshes(meshes), m_RootNodeName(rootNodeName), m_Bones(bone), m_VAO(VertexArray::CreateVertexArray()),
          m_Animations(animations)
    {
        m_VAO->AddVertexBuffer(*(m_Meshes[0].m_VBO));
    }

    void Model::PlayAnimation(const std::string& name)
    {
        if(!m_CurrentAnim)
        {
            for(Animation& anim : *m_Animations)
            {
                if(anim.GetName() == name)
                {
                    anim.Play();
                    m_CurrentAnim = &anim;
                }
            }
        }
        else
            MTN_WARN("Animation {0} is already playing !", m_CurrentAnim->GetName().c_str());
    }

    void Model::StopAnimation()
    {
        if(m_CurrentAnim)
        {
            m_CurrentAnim->Stop();
            m_CurrentAnim = nullptr;
        }
        else
            MTN_WARN("Attempted to stop an animation but nothing is playing !");
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

    void Model::UpdateAnimation()
    {
        double animationProgress = m_CurrentAnim->Update();

    }

} // namespace Mouton
