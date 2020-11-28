#include "EditorPropertiesPanels.h"

#include "Core/Utils/FileUtils.h"

#include "imgui.h"

namespace MtnUtils = Mouton::Utils;

EditorPropertiesPanels* EditorPropertiesPanels::s_Instance;

void EditorPropertiesPanels::ShowSpriteComponentPanel(Mouton::SpriteComponent* spriteComp)
{
    s_Instance->ShowSpriteComponentPanelImpl(spriteComp);
}

void EditorPropertiesPanels::ShowOrthographicCameraComponent(Mouton::OrthographicCameraComponent* cameraComponent)
{
    s_Instance->ShowOrthographicCameraBehaviourPanelImpl(cameraComponent);
}

void EditorPropertiesPanels::Init()
{
    s_Instance = new EditorPropertiesPanels();
}

void EditorPropertiesPanels::Stop()
{
    delete s_Instance;
}

void EditorPropertiesPanels::LoadProjectTextures()
{
    s_Instance->PopulateCache();
}

EditorPropertiesPanels::EditorPropertiesPanels()
    : m_CachedTextures()
{
}

void EditorPropertiesPanels::PopulateCache()
{
    // Populate textures cache

    MtnUtils::Directory dir("Projects/textures");
    const auto& items = dir.GetDirectoryItems();

    for(const auto& item : items)
    {
        auto texture = Mouton::Texture2D::CreateTexture(item.GetPath().c_str());

        // TODO: Handle invalid textures
        // Just adding texture in cache for now note that is a texture 
        // isn't loaded properly the engine will probably crash
        m_CachedTextures[item.GetPath()] = texture;
    }
}

void EditorPropertiesPanels::ShowSpriteComponentPanelImpl(Mouton::SpriteComponent* spriteComp)
{
    ImGui::Text(("SpriteComponent : " + spriteComp->GetComponentName()).c_str());
    ImGui::Separator();

    ImGui::SliderFloat3("Position", glm::value_ptr(spriteComp->position), 0.0f, 100.0f);
    ImGui::SliderFloat2("Scale", glm::value_ptr(spriteComp->scale), 0.0f, 100.0f);
    ImGui::SliderFloat("Rotation", &spriteComp->rotation, -360.0f, 360.0f);

    ImGui::Separator();

    static bool useColor = !spriteComp->isTextured;

    ImGui::Checkbox("Use built'in colors", &useColor);

    if(!useColor)
    {
        static int textureSelected = 1;

        ImGui::TextColored({ 0.0f, 1.0f , 0.5f, 1.0f }, "Please select a texture");

        int i = 0;
        for(auto&[path, texture] : m_CachedTextures)
        {
            if(ImGui::Selectable(path.c_str(), textureSelected == i))
            {
                spriteComp->isTextured = true;
                spriteComp->texture = texture;
            }

            i++;
        }
    }
    else
    {
        if(spriteComp->isTextured)
            spriteComp->isTextured = false;

        ImGui::ColorEdit4("Color", glm::value_ptr(spriteComp->color));
    }
}


void EditorPropertiesPanels::ShowOrthographicCameraBehaviourPanelImpl(Mouton::OrthographicCameraComponent* cameraComponent)
{
    ImGui::Text("Orthographic Camera Component");

    ImGui::SliderFloat3("Camera position", glm::value_ptr(cameraComponent->GetPosition()), -1000.0f, 1000.0f, "%.3f", 5.0f);
    ImGui::SliderFloat("Camera rotation", &cameraComponent->GetRotation(), -360.0f, 360.0f, "%.3f", 5.0f);
}
