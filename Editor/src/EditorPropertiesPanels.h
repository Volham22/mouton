#ifndef EDITOR_PROPERTIES_PANELS_H
#define EDITOR_PROPERTIES_PANELS_H

#include "Renderer/Texture.h"
#include "MoutonComponents/SpriteComponent.h"
#include "MoutonComponents/PythonBehaviourComponent.h"

#include "imgui.h"

class EditorPropertiesPanels
{
public:
    static void Init();
    static void Stop();
    static void LoadProjectTextures();
    static void ShowSpriteComponentPanel(Mouton::SpriteComponent* spriteComponent);
    static void ShowPythonBehaviourComponentPanel(Mouton::PythonBehaviourComponent<Mouton::PythonBinder>* behaviourComponent)
    {
        ImGui::Text(("PythonBehaviour Script ! " + behaviourComponent->GetComponentName()).c_str());
        ImGui::Separator();

        ImGui::Text(("This component refers to file" + behaviourComponent->GetComponentName() + ".py").c_str());
    }

private:
    using CachedTextures = std::unordered_map<std::string, std::shared_ptr<Mouton::Texture2D>>;

    static EditorPropertiesPanels* s_Instance;
    CachedTextures m_CachedTextures;

private:
    EditorPropertiesPanels();
    void PopulateCache();
    void ShowSpriteComponentPanelImpl(Mouton::SpriteComponent* spriteComponent);
};

#endif
