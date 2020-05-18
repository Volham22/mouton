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
        : m_Meshes(meshes), m_RootNodeName(), m_Bones(), m_VAO(VertexArray::CreateVertexArray()),
          m_Animations(), m_CurrentAnim(nullptr)
    {
        m_VAO->AddVertexBuffer(*(m_Meshes[0].m_VBO));
    }

        Model::Model(const std::vector<Mesh>& meshes, const std::unordered_map<std::string, Bone>& bone,
            const std::shared_ptr<std::vector<Animation>>& animations, const std::string& rootNodeName)
        : m_Meshes(meshes), m_RootNodeName(rootNodeName), m_Bones(bone), m_VAO(VertexArray::CreateVertexArray()),
          m_Animations(animations), m_CurrentAnim(nullptr)
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
                {é
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

    void Model::DrawModel(Shader& shader)
    {
        m_VAO->Bind();

        if(m_CurrentAnim)
        {
            m_Bones[m_RootNodeName].Update(m_CurrentAnim->Update(), m_CurrentAnim->GetName());

            int cnt = 0;
            for(auto& [name, bone] : m_Bones)
            {
                shader.SetUniform(std::string("u_Bones[") + std::to_string(cnt) + std::string("]"),
                    bone.GetAnimatedTransform());
                cnt++;
            }
        }

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
