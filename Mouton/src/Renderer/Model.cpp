#include "Model.h"

#include "Platform/Assimp/AssimpModelLoader.h"

namespace Mouton
{

    std::unique_ptr<ModelLoader> ModelLoader::CreateModelLoader(const std::string& path)
    {
        // Only assimp is supported for now
        return std::make_unique<AssimpModelLoader>(path);
    }

    Model::Model(const std::shared_ptr<Node>& rootNode)
        : m_RootNode(rootNode), m_Animations(), m_CurrentAnim(nullptr)
    {
    }

        Model::Model(const std::shared_ptr<std::vector<Animation>>& animations, const std::shared_ptr<Node>& rootNode)
        : m_RootNode(rootNode), m_Animations(animations), m_CurrentAnim(nullptr)
    {
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
            MTN_TRACE("Animation finished");
        }
        else
            MTN_WARN("Attempted to stop an animation but nothing is playing !");
    }

    void Model::DrawModel()
    {
        if(m_CurrentAnim)
        {
            double animProgress = m_CurrentAnim->Update();

            if(animProgress >= 0)
            {
                // glm::mat4 rootTransform = glm::mat4(1.0f);
                m_RootNode->ProcessNodeHierarchy(m_CurrentAnim->GetName(), animProgress, m_RootNode->GetTransformation());
            }
            else
                StopAnimation();
        }

        m_RootNode->Draw();
    }

    std::shared_ptr<std::array<glm::mat4, MTN_MAX_BONES_COUNT>> Model::GetBonesTransforms() const
    {
        auto transforms = std::make_shared<std::array<glm::mat4, MTN_MAX_BONES_COUNT>>();
        m_RootNode->RetrieveBonesTransform(transforms);

        return transforms;
    }


} // namespace Mouton
