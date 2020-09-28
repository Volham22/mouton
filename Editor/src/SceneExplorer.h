#ifndef SCENE_EXPLORER_H
#define SCENE_EXPLORER_H

class EditorLayer;

#include "MoutonPch.h"

#include "Ecs/Components.h"
#include "Ecs/Scene.h"

class SceneExplorer
{
public:
    SceneExplorer() = default;
    void ShowSceneExplorer(Mouton::Scene& scene);

private:
    Mouton::Component* m_ComponentShown = nullptr;

    Mouton::Component* CreateComponentFromType(Mouton::Scene& scene, Mouton::Component::ComponentType type,
        const std::string& name) const;
    void ShowProperties();

    void ShowEntity(Mouton::Entity* entity, Mouton::Scene& scene);
    void ShowComponent(Mouton::Entity* entity ,Mouton::Component* comp, Mouton::Scene& scene);
    void ShowCreateComponent(Mouton::Scene& scene) const;
    void ShowCreateEntity(Mouton::Scene& scene) const;
};

#endif