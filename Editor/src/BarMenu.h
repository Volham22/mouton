#ifndef BAR_MENU_H
#define BAR_MENU_H

#include "Ecs/Scene.h"

class EditorLayer;

class BarMenu
{
public:
    static void ShowMenu(const std::shared_ptr<Mouton::Scene>& scene, EditorLayer* editorLayer);
};

#endif