#ifndef MODEL_H
#define MODEL_H

#include "MoutonPch.h"

#include "VertexArray.h"
#include "Mesh.h"
#include "Animations/Bone.h"
#include "Animations/Animation.h"

namespace Mouton
{

    class Model
    {
    public:
        Model(const std::vector<Mesh>& meshes);
        Model(const std::vector<Mesh>& meshes, const std::unordered_map<std::string, Bone>& bone);
        void DrawModel();
    
    private:
        std::vector<Mesh> m_Meshes;
        std::unordered_map<std::string, Bone> m_Bones;
        std::shared_ptr<VertexArray> m_VAO;
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