#ifndef MODEL_H
#define MODEL_H

#include "MoutonPch.h"

#include "Shader.h"
#include "VertexArray.h"
#include "Mesh.h"
#include "Node.h"
#include "Animations/Bone.h"
#include "Animations/Animation.h"

namespace Mouton
{

    class Model
    {
    public:
        Model(const std::shared_ptr<Node>& rootNode);
        Model(const std::shared_ptr<std::vector<Animation>>& animations,
            const std::shared_ptr<Node>& rootNode);
        void PlayAnimation(const std::string& name);
        void StopAnimation();
        void DrawModel();
        std::shared_ptr<std::array<glm::mat4, MTN_MAX_BONES_COUNT>> GetBonesTransforms() const;
    
    private:
        std::shared_ptr<Node> m_RootNode;
        std::shared_ptr<std::vector<Animation>> m_Animations;

        Animation* m_CurrentAnim;
    };

    class ModelLoader
    {
    public:
        virtual bool Load() = 0;
        virtual std::shared_ptr<Model>& GetLoadedModel() = 0;
        virtual std::shared_ptr<std::vector<Animation>>& GetModelAnimations() = 0;

        static std::unique_ptr<ModelLoader> CreateModelLoader(const std::string& path);
    };

} // namespace Mouton


#endif