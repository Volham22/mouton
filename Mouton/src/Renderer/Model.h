#ifndef MODEL_H
#define MODEL_H

#include "MoutonPch.h"

#include "VertexArray.h"
#include "Mesh.h"

namespace Mouton
{

    class Model
    {
    public:
        Model(const std::vector<Mesh>& meshes);
        void DrawModel();
    
    private:
        std::vector<Mesh> m_Meshes;
        std::shared_ptr<VertexArray> m_VAO;
    };

    class ModelLoader
    {
    public:
        virtual bool Load() = 0;
        virtual std::shared_ptr<Model>& GetLoadedModel() = 0;

        static std::unique_ptr<ModelLoader> CreateModelLoader(const std::string& path);
    };

} // namespace Mouton


#endif