#ifndef EDITOR_PROPERTIES_PANELS_H
#define EDITOR_PROPERTIES_PANELS_H

#include "MoutonComponents/SpriteComponent.h"
#include "MoutonComponents/PythonBehaviourComponent.h"

#include "imgui.h"

#include <type_traits>

class EditorPropertiesPanels
{
public:
    static void ShowSpriteComponentPanel(Mouton::SpriteComponent* spriteComponent);

    static void ShowPythonBehaviourComponentPanel(Mouton::PythonBehaviourComponent<Mouton::PythonBinder>* behaviourComponent)
    {
        ImGui::Text(("PythonBehaviour Script ! " + behaviourComponent->GetComponentName()).c_str());
        ImGui::Separator();

        ImGui::Text(("This component refers to file" + behaviourComponent->GetComponentName() + ".py").c_str());
    }
};

#endif