#include "EditorLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "MoutonComponents/TransformComponent.h"
#include "MoutonComponents/Material2DComponent.h"

#include "EditorPropertiesPanels.h"

using namespace Mouton;

static Component* CreateComponentFromType(Component::ComponentType type, const std::string& name)
{
    switch(type)
    {
        case Component::ComponentType::Material2DComponent:
            return new Material2DComponent(name);
        case Component::ComponentType::Transform:
            return new TransformComponent(name);
        
        default:
            return nullptr;
    }
}

EditorLayer::EditorLayer()
    : Layer("Editor Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene(),
      m_ComponentShown(nullptr)
{
    RendererContext::InitContext(GraphicAPI::OpenGL);
    Renderer::InitRenderer();
    Renderer2D::Init();

    m_ViewportFramebuffer = Framebuffer::CreateFramebuffer();

    m_Scene.AddEntity(new Entity("RedQuad"));
    m_Scene.AddEntity(new Entity("GreenQuad"));

    {
        using Type = Component::ComponentType;
        m_Scene.AddComponent(Type::Transform, new TransformComponent());
        m_Scene.AddComponent(Type::Material2DComponent, new Material2DComponent());
        m_Scene.AddComponentToEntity("RedQuad", Type::Transform, "TransformComponent");
        m_Scene.AddComponentToEntity("GreenQuad", Type::Transform, "TransformComponent");
    }
}

void EditorLayer::OnBind()
{
}

void EditorLayer::OnUnbind()
{
    Renderer2D::EndScene();
}

void EditorLayer::OnUpdate()
{
    static ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    static bool dockSpaceOpened = true;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PopStyleVar(2);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Dockspace", &dockSpaceOpened, window_flags);
    ImGui::PopStyleVar();

    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockFlags);

    ImGui::End();

    // m_ViewportFramebuffer->CreateBlankTexture(500, 500);

    ImGui::Begin("Game Viewport");
    static uint32_t textureID = m_ViewportFramebuffer->GetTextureAttachmentID();

    auto[width, height] = ImGui::GetContentRegionAvail();
    m_Camera.SetCoords(0.0f, height, 0.0f, height);
    m_ViewportFramebuffer->CreateBlankTexture(width, height);

    ImGui::Image((void*)textureID, { width, height });
    ImGui::End();

    ImGui::Begin("Performance window");
    ImGui::Text("Mouton Performance.");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
        1000.0f / ImGui::GetIO().Framerate,
        ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("Scene explorer");

    if(ImGui::CollapsingHeader("Scene Entities"))
    {
        const auto& entities = m_Scene.GetEntities();

        for(Entity* ent : entities)
        {
            if(ImGui::TreeNode(ent->GetName().c_str()))
            {
                const auto& entityComponents = m_Scene.GetEntityComponent(ent->GetName());

                for(Component* comp : entityComponents)
                {
                    if(ImGui::TreeNode(comp->GetComponentName().c_str()))
                    {
                        if(ImGui::Button("Remove", { 150, 20 }))
                        {
                            m_Scene.RemoveComponentToEntity(ent->GetName().c_str(),
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

                    const auto& components = m_Scene.GetComponents(Component::ComponentType::Any);
                    for(Component* comp : components)
                    {
                        if(ImGui::Selectable(comp->GetComponentName().c_str()))
                            m_Scene.AddComponentToEntity(ent->GetName().c_str(), comp->GetComponentType(), comp->GetComponentName().c_str());
                    }

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
            ImGui::Combo("Select Component Type", &item, "Transform\0Material2D\0\0", 5);
            ImGui::InputTextWithHint("Component Name", "type a name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
            ImGui::Separator();

            auto toComponentType = [](auto x) {
                return (Component::ComponentType)(x + 1);
            };

            if(ImGui::Button("Add"))
            {
                if(std::strlen(nameBuffer) > 0 && m_Scene.AddComponent(toComponentType(item),
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
                if(strlen(entityNameBuffer) > 0 && strlen(entityNameBuffer) < 200 && m_Scene.AddEntity(new Entity(std::string(entityNameBuffer))))
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

    // Viewport rendering
    m_ViewportFramebuffer->Bind();
    Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());

    for (int i = 0; i < 100; i += 20)
    {
        for (int j = 0; j < 100; j += 20)
            Renderer2D::DrawQuad({10.0f + i, 10.0f + j, 0.0f}, {10.0f, 10.0f}, {1.0f, 0.0f, 0.75f, 1.0f});
    }

    Renderer2D::EndScene();
    m_ViewportFramebuffer->Unbind();
}

bool EditorLayer::OnEvent(Event &event)
{
    EventSystem::ApplyFunction<WindowCloseEvent>(&event, [](Event &event) -> bool {
        MTN_INFO("On window close ...");
        return true;
    });

    EventSystem::ApplyFunction<MouseScrolledEvent>(&event, [](Event& event) -> bool {
        MTN_TRACE("Mouse scrolled !");
        return true;
    });

    return event.Handled();
}

void EditorLayer::ShowProperties()
{
    using Type = Mouton::Component::ComponentType;

    switch(m_ComponentShown->GetComponentType())
    {
        case Type::Transform:
            EditorPropertiesPanels::ShowTransformComponent(reinterpret_cast<TransformComponent*>(m_ComponentShown));
            break;
        
        case Type::Material2DComponent:
            EditorPropertiesPanels::ShowMaterial2DComponent(reinterpret_cast<Material2DComponent*>(m_ComponentShown));
            break;
        
        default:
            MTN_WARN("Unknown Component Properties to show !");
    }

}