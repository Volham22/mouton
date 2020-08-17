#include "EditorPropertiesPanels.h"

#include "imgui.h"

// void EditorPropertiesPanels::ShowTransformComponent(Mouton::TransformComponent* transformComponent)
// {
//     ImGui::Text(("Transform Component : " + transformComponent->GetComponentName()).c_str());
//     ImGui::Separator();

//     ImGui::SliderFloat3("Position", glm::value_ptr(transformComponent->Transform), -10000.0f, 10000.0f, "%.3f");

//     if(ImGui::Button("Reset Position"))
//         transformComponent->Transform = { 0.0f, 0.0f, 0.0f };

//     ImGui::SliderFloat3("Rotation", glm::value_ptr(transformComponent->Rotation), -10000.0f, 10000.0f, "%.3f");

//     if(ImGui::Button("Reset Rotation"))
//         transformComponent->Rotation = { 0.0f, 0.0f, 0.0f };

//     ImGui::SliderFloat3("Scale   ", glm::value_ptr(transformComponent->Scale), -10000.0f, 10000.0f, "%.3f");

//     if(ImGui::Button("Reset Scale   "))
//         transformComponent->Scale = { 0.0f, 0.0f, 0.0f };
// }

// void EditorPropertiesPanels::ShowMaterial2DComponent(Mouton::Material2DComponent* materialComponent)
// {
//     ImGui::Text(("Material2D Component : " + materialComponent->GetComponentName()).c_str());
//     ImGui::Separator();

//     ImGui::Checkbox("Textured", &materialComponent->IsTextured);

//     if(materialComponent->IsTextured)
//     {
//         ImGui::Text(("File : " + materialComponent->GetComponentName()).c_str());
//         ImGui::SameLine();
//         if(ImGui::Button("Browse ..."))
//             MTN_TRACE("Not implemented.");
//     }
//     else
//         ImGui::ColorPicker4("Material color", glm::value_ptr(materialComponent->Color));
    
// }