#ifndef SCENE_EXPLORER_H
#define SCENE_EXPLORER_H

class EditorLayer;

#include "MoutonPch.h"

#include "Ecs/Components.h"
#include "Ecs/Scene.h"
#include "Renderer/OrthographicCameraController.h"

class SceneExplorer
{
public:
    SceneExplorer();
    ~SceneExplorer();

    void InitProperties();
    void ShowSceneExplorer(std::shared_ptr<Mouton::Scene>& scene);
    auto& GetUserCamera() { return m_CustomCamera; }
    void SetUserCamera(Mouton::OrthographicCameraController* camera);
    void SetDefaultCamera();

private:
    Mouton::Component* m_ComponentShown;
    std::shared_ptr<Mouton::OrthographicCamera> m_CustomCamera;

    Mouton::Component* CreateComponentFromType(std::shared_ptr<Mouton::Scene>& scene, Mouton::Component::ComponentType type,
        const std::string& name) const;
    void ShowProperties();

    void ShowEntity(Mouton::Entity* entity, std::shared_ptr<Mouton::Scene>& scene);
    void ShowComponent(Mouton::Entity* entity ,Mouton::Component* comp, std::shared_ptr<Mouton::Scene>& scene);
    void ShowCreateComponent(std::shared_ptr<Mouton::Scene>& scene) const;
    void ShowCreateEntity(std::shared_ptr<Mouton::Scene>& scene) const;
};

#endif