#include "EditorLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "MoutonComponents/SpriteComponent.h"
#include "MoutonComponents/PythonBehaviourComponent.h"
#include "Scripting/PythonBehaviourBinder.h"
#include "Scripting/PythonScriptEngine.h"

#include "EditorPropertiesPanels.h"
#include "SceneExplorer.h"


EditorLayer::EditorLayer()
    : Layer("Editor Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene(),
      m_ComponentShown(nullptr)
{
    Mouton::RendererContext::InitContext(Mouton::GraphicAPI::OpenGL);
    Mouton::Renderer::InitRenderer();
    Mouton::Renderer2D::Init();
    Mouton::PythonScriptEngine::Init();

    m_ViewportFramebuffer = Mouton::Framebuffer::CreateFramebuffer();

    m_Scene.AddEntity(new Mouton::Entity("RedQuad"));
    m_Scene.AddEntity(new Mouton::Entity("GreenQuad"));

    {
        using Type = Mouton::Component::ComponentType;

        Mouton::SpriteComponent* red = new Mouton::SpriteComponent("RedSprite");
        Mouton::SpriteComponent* green = new Mouton::SpriteComponent("GreenSprite");
        Mouton::PythonBehaviourComponent<Mouton::SpriteComponentScriptable>* behaviour = new Mouton::PythonBehaviourComponent<Mouton::SpriteComponentScriptable>("RedSprite", "RedSprite", red);

        m_Scene.AddComponent(Type::SpriteComponent, red);
        m_Scene.AddComponent(Type::SpriteComponent, green);
        m_Scene.AddComponent(Type::PythonBehaviourComponent, behaviour);
        m_Scene.AddComponentToEntity("RedQuad", Type::SpriteComponent, "RedSprite");
        m_Scene.AddComponentToEntity("RedQuad", Type::PythonBehaviourComponent, "RedSprite");
        m_Scene.AddComponentToEntity("GreenQuad", Type::SpriteComponent, "GreenSprite");
    }
}

void EditorLayer::OnBind()
{
    m_Scene.ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);
            behaviour.pythonBehaviour->OnSceneBegin();
        });
}

void EditorLayer::OnUnbind()
{
    m_Scene.ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);
            behaviour.pythonBehaviour->OnSceneEnd();
        });

    Mouton::Renderer2D::EndScene();
}

void EditorLayer::OnUpdate()
{
    m_Scene.ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);
            behaviour.pythonBehaviour->OnSceneUpdate();
        });
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

EditorLayer::~EditorLayer()
{
    Mouton::PythonScriptEngine::Stop();
}
