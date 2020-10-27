#include "EditorPropertiesPanels.h"

#include "Core/Utils/FileUtils.h"

#include "imgui.h"

void EditorPropertiesPanels::ShowSpriteComponentPanel(Mouton::SpriteComponent* spriteComp)
{
    ImGui::Text(("SpriteComponent : " + spriteComp->GetComponentName()).c_str());
    ImGui::Separator();

    ImGui::SliderFloat3("Position", glm::value_ptr(spriteComp->position), 0.0f, 100.0f);
    ImGui::SliderFloat2("Scale", glm::value_ptr(spriteComp->scale), 0.0f, 100.0f);
    ImGui::SliderFloat("Rotation", &spriteComp->rotation, -360.0f, 360.0f);

    ImGui::Separator();

    ImGui::Checkbox("Has texture", &spriteComp->isTextured);

    if(spriteComp->isTextured)
    {
        namespace MtnUtils = Mouton::Utils;

        MtnUtils::Directory dir("Projects/textures");
        const auto& items = dir.GetDirectoryItems();

        static int textureSelected = -1;

        ImGui::TextColored({ 0.0f, 1.0f , 0.5f, 1.0f }, "Please select a texture");

        for(uint32_t i = 0; i < items.size(); i++)
        {
            if(ImGui::Selectable(items[i].GetPath().c_str(), textureSelected == i))
                MTN_TRACE("Item selected");
        }
    }
    else
        ImGui::ColorEdit4("Color", glm::value_ptr(spriteComp->color));
}