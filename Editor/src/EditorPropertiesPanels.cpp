#include "EditorPropertiesPanels.h"

#include "imgui.h"

void EditorPropertiesPanels::ShowSpriteComponentPanel(Mouton::SpriteComponent* spriteComp)
{
    ImGui::Text(("SpriteComponent : " + spriteComp->GetComponentName()).c_str());
    ImGui::Separator();

    ImGui::SliderFloat3("Position", glm::value_ptr(spriteComp->position), 0.0f, 100.0f);
    ImGui::SliderFloat2("Scale", glm::value_ptr(spriteComp->scale), 0.0f, 100.0f);
    ImGui::SliderFloat("Rotation", &spriteComp->rotation, -360.0f, 360.0f);

    if(spriteComp->isTextured)
    {
        // TODO: Implement textured quad
        ImGui::Text("Textured Quad are not implemented yet :(");
    }
    else
        ImGui::ColorEdit4("Color", glm::value_ptr(spriteComp->color));
    
}