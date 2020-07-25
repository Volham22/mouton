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

    Mouton::Component* CreateComponentFromType(Mouton::Component::ComponentType type, const std::string& name);
    void ShowProperties();
};

#endif