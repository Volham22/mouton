#include "EditorLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "MoutonComponents/TransformComponent.h"
#include "MoutonComponents/Material2DComponent.h"

#include "EditorPropertiesPanels.h"
#include "SceneExplorer.h"


EditorLayer::EditorLayer()
    : Layer("Editor Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene(),
      m_ComponentShown(nullptr)
{
    Mouton::RendererContext::InitContext(Mouton::GraphicAPI::OpenGL);
    Mouton::Renderer::InitRenderer();
    Mouton::Renderer2D::Init();

    m_ViewportFramebuffer = Mouton::Framebuffer::CreateFramebuffer();

    m_Scene.AddEntity(new Mouton::Entity("RedQuad"));
    m_Scene.AddEntity(new Mouton::Entity("GreenQuad"));

    {
        using Type = Mouton::Component::ComponentType;
        m_Scene.AddComponent(Type::Transform, new Mouton::TransformComponent());
        m_Scene.AddComponent(Type::Material2DComponent, new Mouton::Material2DComponent());
        m_Scene.AddComponentToEntity("RedQuad", Type::Transform, "TransformComponent");
        m_Scene.AddComponentToEntity("GreenQuad", Type::Transform, "TransformComponent");
    }
}

void EditorLayer::OnBind()
{
}

void EditorLayer::OnUnbind()
{
    Mouton::Renderer2D::EndScene();
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

    // Does ImGui calls for the Scene explorer
    m_SceneExplorer.ShowSceneExplorer(m_Scene);

    // Viewport rendering
    m_ViewportFramebuffer->Bind();
    Mouton::Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());

    for (int i = 0; i < 100; i += 20)
    {
        for (int j = 0; j < 100; j += 20)
            Mouton::Renderer2D::DrawQuad({10.0f + i, 10.0f + j, 0.0f}, {10.0f, 10.0f}, {1.0f, 0.0f, 0.75f, 1.0f});
    }

    Mouton::Renderer2D::EndScene();
    m_ViewportFramebuffer->Unbind();
}

bool EditorLayer::OnEvent(Mouton::Event &event)
{
    Mouton::EventSystem::ApplyFunction<Mouton::WindowCloseEvent>(&event, [](Mouton::Event &event) -> bool {
        MTN_INFO("On window close ...");
        return true;
    });

    Mouton::EventSystem::ApplyFunction<Mouton::MouseScrolledEvent>(&event, [](Mouton::Event& event) -> bool {
        MTN_TRACE("Mouse scrolled !");
        return true;
    });

    return event.Handled();
}