#include "EditorLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "MoutonComponents/TransformComponent.h"
#include "MoutonComponents/Material2DComponent.h"

using namespace Mouton;

EditorLayer::EditorLayer()
    : Layer("Editor Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene()
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
                            MTN_TRACE("Not implemented yet");

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
    }

    ImGui::End();

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

    return event.Handled();
}