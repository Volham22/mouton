#include "SceneExplorer.h"

#include "imgui.h"
#include "Ecs/Entity.h"

#include "EditorPropertiesPanels.h"

using namespace Mouton;


void SceneExplorer::ShowSceneExplorer(Scene& scene)
{
    ImGui::Begin("Scene explorer");

    if(ImGui::CollapsingHeader("Scene Entities"))
    {
        const auto& entities = scene.GetEntities();

        for(Entity* ent : entities)
        {
            if(ImGui::TreeNode(ent->GetName().c_str()))
            {
                const auto& entityComponents = scene.GetEntityComponent(ent->GetName());

                for(Component* comp : entityComponents)
                {
                    if(ImGui::TreeNode(comp->GetComponentName().c_str()))
                    {
                        if(ImGui::Button("Remove", { 150, 20 }))
                        {
                            scene.RemoveComponentToEntity(ent->GetName().c_str(),
                                comp->GetComponentType(),
                                comp->GetComponentName());
                        }

                        if(ImGui::Button("Show properties", { 150, 20 }))
                            m_ComponentShown = comp;

                        ImGui::TreePop();
                    }
                }

                if(ImGui::Button("Add Component"))
                    ImGui::OpenPopup("components_add");

                if(ImGui::BeginPopup("components_add"))
                {
                    ImGui::Text("Choose a component to add");
                    ImGui::Separator();

                    const auto& components = scene.GetComponents(Component::ComponentType::Any);
                    for(Component* comp : components)
                    {
                        if(ImGui::Selectable(comp->GetComponentName().c_str()))
                            scene.AddComponentToEntity(ent->GetName().c_str(), comp->GetComponentType(), comp->GetComponentName().c_str());
                    }

                    ImGui::EndPopup();
                }

                ImGui::SameLine();
                if(ImGui::Button("Remove entity"))
                    ImGui::OpenPopup("Do you really want to do it ?");
                
                if(ImGui::BeginPopup("Do you really want to do it ?"))
                {
                    ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "You're about to remove an entity do you really want to do it ?");
                    ImGui::Separator();

                    if(ImGui::Button("Yes"))
                        scene.RemoveEntity(ent->GetName());
                    
                    ImGui::SameLine();

                    if(ImGui::Button("No keep my entity !"))
                        ImGui::CloseCurrentPopup();

                    ImGui::EndPopup();
                }

                ImGui::TreePop();
            }

            ImGui::Separator();
        }

        if(ImGui::Button("Create a new Component ..."))
            ImGui::OpenPopup("Create component");
        
        if(ImGui::BeginPopupModal("Create component", nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove))
        {
            static char nameBuffer[200] = "";
            ImGui::Text("Create a new Component");
            static int item = 1;
            // The item value must match with the Mouton::Component::ComponentType enum
            ImGui::Combo("Select Component Type", &item, "SpriteComponent\0Behaviour Component\0\0", 5);
            ImGui::InputTextWithHint("Component Name", "type a name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
            ImGui::Separator();

            auto toComponentType = [](auto x) {
                return (Component::ComponentType)(x + 1);
            };

            if(ImGui::Button("Add"))
            {
                if(std::strlen(nameBuffer) > 0 && scene.AddComponent(toComponentType(item),
                    CreateComponentFromType(toComponentType(item), std::string(nameBuffer))))
                    ImGui::CloseCurrentPopup();
                else
                    ImGui::OpenPopup("Incorrect Name !");
            }

            if(ImGui::BeginPopupModal("Incorrect Name !"))
            {
                ImGui::Text("Component name not valid or already used !");
                ImGui::Separator();

                if(ImGui::Button("Close."))
                    ImGui::CloseCurrentPopup();
                
                ImGui::EndPopup();
            }

            ImGui::SameLine();
            if(ImGui::Button("Cancel"))
                ImGui::CloseCurrentPopup();
            
            ImGui::EndPopup();
        }

        ImGui::SameLine();
        if(ImGui::Button("Add new Entity"))
            ImGui::OpenPopup("Add Entity");
        
        if(ImGui::BeginPopupModal("Add Entity"))
        {
            ImGui::Text("Add a new entity");
            static char entityNameBuffer[200] = "";

            ImGui::InputTextWithHint("Entity name", "enter new entity name ...", entityNameBuffer, IM_ARRAYSIZE(entityNameBuffer));

            ImGui::Separator();
            if(ImGui::Button("Add Entity"))
            {
                if(strlen(entityNameBuffer) > 0 && strlen(entityNameBuffer) < 200 && scene.AddEntity(new Entity(std::string(entityNameBuffer))))
                    ImGui::CloseCurrentPopup();
                else
                    ImGui::OpenPopup("Incorrect Entity name !");
            }

            if(ImGui::BeginPopupModal("Incorrect Entity name !"))
            {
                ImGui::Text("Entity name not valid or already used !");
                ImGui::Separator();

                if(ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();

                ImGui::EndPopup();
            }

            ImGui::SameLine();
            if(ImGui::Button("Cancel."))
                ImGui::CloseCurrentPopup();
            
            ImGui::EndPopup();
        }
    }

    ImGui::End();

    // Show Component Properties panel if any is selected
    if(m_ComponentShown)
    {
        ImGui::Begin("Component Properties");
        ShowProperties();
        ImGui::End();
    }
}

Component* SceneExplorer::CreateComponentFromType(Component::ComponentType type, const std::string& name)
{
    switch(type)
    {
        case Component::ComponentType::SpriteComponent:
            return new SpriteComponent(name);
        
        default:
            return nullptr;
    }
}

void SceneExplorer::ShowProperties()
{
    using Type = Component::ComponentType;

    switch(m_ComponentShown->GetComponentType())
    {
        case Type::SpriteComponent:
            EditorPropertiesPanels::ShowSpriteComponentPanel(reinterpret_cast<SpriteComponent*>(m_ComponentShown));
            break;

        default:
            MTN_WARN("Unknown Component Properties to show !");
    }
}