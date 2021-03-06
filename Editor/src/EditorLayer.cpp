#include "EditorLayer.h"

#include "imgui.h"

#include "Engine.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "MoutonComponents/SpriteComponent.h"
#include "MoutonComponents/PythonBehaviourComponent.h"
#include "Scripting/PythonBehaviourBinder.h"
#include "Scripting/PythonScriptEngine.h"
#include "Scripting/ScriptSkeletonFactory.h"

#include "EditorPropertiesPanels.h"
#include "SceneExplorer.h"
#include "BarMenu.h"

#include <rapidjson/prettywriter.h>


EditorLayer::EditorLayer()
    : Layer("Editor Layer"), m_Camera(-100.0f, 100.0f, -100.0f, 100.0f), m_Scene(new Mouton::Scene()),
      m_ComponentShown(nullptr), m_ScenePlaying(SceneStates::Stopped), m_Logger()
{
    Mouton::RendererContext::InitContext(Mouton::GraphicAPI::OpenGL);
    Mouton::Renderer::InitRenderer();
    Mouton::Renderer2D::Init();

    // Initialize PythonScriptEngine engine to enable scripted scene loading
    Mouton::PythonScriptEngine::Init();

    // This will load texures and some other stuff in the future
    // Since this method loads textures, the Renderer context has to be
    // initialized before.
    // InitProperties must be called AFTER Mouton::RendererContext::InitContext();
    m_SceneExplorer.InitProperties();

    m_ViewportFramebuffer = Mouton::Framebuffer::CreateFramebuffer();
}

void EditorLayer::OnBind()
{
}

void EditorLayer::OnUnbind()
{
}

void EditorLayer::OnUpdate(Mouton::Timestep delta)
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
    BarMenu::ShowMenu(m_Scene, this);
    ImGui::End();

    ImGui::Begin("Game Viewport");

    auto[width, height] = ImGui::GetContentRegionAvail();
    m_Camera.SetCoords(0.0f, height, 0.0f, width);
    m_ViewportFramebuffer->CreateBlankTexture(width, height);
    uint32_t textureID = m_ViewportFramebuffer->GetTextureAttachmentID();

    ImGui::Image((void*)textureID, { width, height });
    ImGui::End();

    ImGui::Begin("Debug Performance window");
    ImGui::Text("Mouton Performance.");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
        1000.0f / ImGui::GetIO().Framerate,
        ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Begin("Scene control");

    auto freeSpace = ImGui::GetContentRegionAvail();

    freeSpace.x /= 3;

    if(ImGui::Button("Start Scene", freeSpace))
    {
        if(m_ScenePlaying == SceneStates::Paused)
        {
            m_ScenePlaying = SceneStates::Playing;
            OnSceneResume();
        }

        if(m_ScenePlaying == SceneStates::Stopped)
        {
            m_ScenePlaying = SceneStates::Playing;
            OnSceneStart();
        }

        m_Logger.AddLog("Scene started\n");
    }

    ImGui::SameLine();

    if(ImGui::Button("Pause scene", freeSpace))
    {
        if(m_ScenePlaying == SceneStates::Playing)
        {
            m_ScenePlaying = SceneStates::Paused;
            m_Logger.AddLog("Scene Paused\n");
            OnScenePause();
        }
    }

    ImGui::SameLine();

    if(ImGui::Button("Stop Scene", freeSpace))
    {
        if(m_ScenePlaying == SceneStates::Paused || m_ScenePlaying == SceneStates::Playing)
        {
            m_ScenePlaying = SceneStates::Stopped;
            m_Logger.AddLog("Scene stopped\n");
            OnSceneStop();
        }
    }

    ImGui::End();

    if(m_ScenePlaying == SceneStates::Playing)
        OnSceneUpdate(delta);

    m_Logger.Draw("Mouton Logger");

    // Does ImGui calls for the Scene explorer
    m_SceneExplorer.ShowSceneExplorer(m_Scene, m_PythonErrorCb);
}

void EditorLayer::OnRender()
{
    // Viewport rendering
    m_ViewportFramebuffer->Bind();
    if(m_SceneExplorer.GetUserCamera())
        Mouton::Renderer2D::BeginScene(m_SceneExplorer.GetUserCamera()->GetViewProjectionMatrix());
    else
        Mouton::Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());

    m_Scene->ForEachComponents(Mouton::Component::ComponentType::SpriteComponent, [](Mouton::Component& comp) {
        Mouton::SpriteComponent& sprite = static_cast<Mouton::SpriteComponent&>(comp);

        if(sprite.isTextured)
            Mouton::Renderer2D::DrawQuad(sprite.position, sprite.scale, sprite.texture, sprite.rotation);
        else
            Mouton::Renderer2D::DrawQuad(sprite.position, sprite.scale, sprite.color, sprite.rotation);
    });

    Mouton::Renderer2D::EndScene();
    m_ViewportFramebuffer->Unbind();
}

bool EditorLayer::OnEvent(Mouton::Event &event)
{
    Mouton::EventSystem::ApplyFunction<Mouton::WindowCloseEvent>(&event, [](Mouton::Event &event) -> bool {
        MTN_INFO("On window close ...");
        Mouton::PythonScriptEngine::Stop();
        Mouton::Application::SetApplicationShouldStop(true);
        return true;
    });

    Mouton::EventSystem::ApplyFunction<Mouton::MouseScrolledEvent>(&event, [](Mouton::Event& event) -> bool {
        MTN_TRACE("Mouse scrolled !");
        return true;
    });

    return event.Handled();
}

void EditorLayer::SetScene(std::shared_ptr<Mouton::Scene>& scene)
{
    m_ComponentShown = nullptr;
    m_Scene = scene;

    scene->ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [this](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);

            behaviour.pythonBehaviour->SetPythonErrorCallback(m_PythonErrorCb);
        });
}

void EditorLayer::OnSceneStart()
{
    Mouton::PythonScriptEngine::Init();
    MTN_TRACE("Scene Started");

    m_Scene->ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);

            if(behaviour.pythonBehaviour->LoadScript() &&
                behaviour.pythonBehaviour->GetBoundComponent())
                behaviour.pythonBehaviour->OnSceneBegin();
    });
}

void EditorLayer::OnSceneUpdate(Mouton::Timestep delta)
{
    m_Scene->ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [delta](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);

            if(behaviour.pythonBehaviour->GetBoundComponent()
                && behaviour.pythonBehaviour->IsLoaded())
                behaviour.pythonBehaviour->OnSceneUpdate(delta);
    });
}

void EditorLayer::OnScenePause()
{
    MTN_TRACE("Scene paused");
}

void EditorLayer::OnSceneResume()
{
    MTN_TRACE("Scene resumed");
}

void EditorLayer::OnSceneStop()
{
    MTN_TRACE("Scene stopped");

    m_Scene->ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent, [](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);

            if(behaviour.pythonBehaviour->GetBoundComponent() &&
                behaviour.pythonBehaviour->IsLoaded())
                behaviour.pythonBehaviour->OnSceneEnd();
    });
}

EditorLayer::~EditorLayer()
{
    if(m_ScenePlaying == SceneStates::Paused || m_ScenePlaying == SceneStates::Playing)
        Mouton::PythonScriptEngine::Stop();
}
