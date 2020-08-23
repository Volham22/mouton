#include "EditorLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "MoutonComponents/SpriteComponent.h"
#include "Scripting/ElementBehaviour.h"

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

        Mouton::SpriteComponent* red = new Mouton::SpriteComponent("RedSprite");
        Mouton::SpriteComponent* green = new Mouton::SpriteComponent("GreenSprite");
        Mouton::Behaviour<Mouton::SpriteComponent>*  behaviour = new Mouton::Behaviour(red, "RedQuadBehaviour");

        behaviour->SetOnSceneUpdate([](Mouton::SpriteComponent& comp) {
            comp.color.r += 0.01f;

            if(comp.color.r >= 1.0f)
                comp.color.r = 0.0f;
        });

        red->position = { 25.0f, 2.0f, 0.0f };
        red->scale = { 5.0f, 5.0f };

        green->position = { 75.0f, 32.0f, 0.0f };
        green->scale = { 3.0f, 6.0f };
        green->color = { 0.0f, 1.0f, 0.0f, 1.0f };

        m_Scene.AddComponent(Type::SpriteComponent, red);
        m_Scene.AddComponent(Type::SpriteComponent, green);
        m_Scene.AddComponent(Type::BehaviourComponent, behaviour);
        m_Scene.AddComponentToEntity("RedQuad", Type::SpriteComponent, "RedSprite");
        MTN_ASSERT(m_Scene.AddComponentToEntity("RedQuad", Type::BehaviourComponent, "RedQuadBehaviour"), "Not added");
        m_Scene.AddComponentToEntity("GreenQuad", Type::SpriteComponent, "GreenSprite");
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
    using Type = Mouton::Component::ComponentType;

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

    ImGui::Begin("Game Viewport");

    auto[width, height] = ImGui::GetContentRegionAvail();
    m_Camera.SetCoords(0.0f, height, 0.0f, width);
    m_ViewportFramebuffer->CreateBlankTexture(width, height);
    uint32_t textureID = m_ViewportFramebuffer->GetTextureAttachmentID();

    ImGui::Image((void*)textureID, { width, height });
    ImGui::End();

    ImGui::Begin("Performance window");
    ImGui::Text("Mouton Performance.");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
        1000.0f / ImGui::GetIO().Framerate,
        ImGui::GetIO().Framerate);
    ImGui::End();

    // Update Behaviour component if any
    m_Scene.ForEachComponents(Type::BehaviourComponent, [](Mouton::Component& comp) {
        auto& behaviour = MTN_COMPONENT_TO_BEHAVIOUR(comp);
        behaviour.DoUpdate();
    });

    // Viewport rendering
    m_ViewportFramebuffer->Bind();
    Mouton::Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());

    m_Scene.ForEachComponents(Type::SpriteComponent, [](Mouton::Component& comp) {
        Mouton::SpriteComponent& sprite = static_cast<Mouton::SpriteComponent&>(comp);
        // MTN_INFO("Render {}", sprite.GetComponentName().c_str());

        if(sprite.isTextured)
            Mouton::Renderer2D::DrawQuad(sprite.position, sprite.scale, sprite.texture, sprite.rotation);
        else
            Mouton::Renderer2D::DrawQuad(sprite.position, sprite.scale, sprite.color, sprite.rotation);
    });

    Mouton::Renderer2D::EndScene();
    m_ViewportFramebuffer->Unbind();

    // Does ImGui calls for the Scene explorer
    m_SceneExplorer.ShowSceneExplorer(m_Scene);
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
