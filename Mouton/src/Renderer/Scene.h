#ifndef SCENE_H
#define SCENE_H

#include "MoutonPch.h"

#include "VertexArray.h"
#include "Mesh.h"

namespace Mouton
{

    class Scene
    {
    public:
        Scene(const std::vector<Mesh>& meshes);
        void DrawScene();
    
    private:
        std::vector<Mesh> m_Meshes;
        std::shared_ptr<VertexArray> m_VAO;
    };

    class SceneLoader
    {
    public:
        virtual bool Load() = 0;
        virtual std::shared_ptr<Scene>& GetLoadedScene() = 0;

        static std::unique_ptr<SceneLoader> CreateSceneLoader(const std::string& path);
    };

} // namespace Mouton


#endif