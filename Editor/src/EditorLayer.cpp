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
    : Layer("Editor Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene(new Mouton::Scene()),
      m_ComponentShown(nullptr), m_ScenePlaying(SceneStates::Stopped)
{
    Mouton::RendererContext::InitContext(Mouton::GraphicAPI::OpenGL);
    Mouton::Renderer::InitRenderer();
    Mouton::Renderer2D::Init();
    Mouton::PythonScriptEngine::Init();

    // This will load texures and some other stuff in the future
    // Since this method loads textures, the Renderer context has to be
    // initialized before.
    // InitProperties must be called AFTER Mouton::RendererContext::InitContext();
    m_SceneExplorer.InitProperties();

    m_ViewportFramebuffer = Mouton::Framebuffer::CreateFramebuffer();

    m_Scene->AddEntity(new Mouton::Entity("RedQuad"));
    m_Scene->AddEntity(new Mouton::Entity("GreenQuad"));

    {
        using Type = Mouton::Component::ComponentType;

        auto cameraInstance =
            new Mouton::OrthographicCameraController(std::make_shared<Mouton::OrthographicCamera>(0.0f, 100.0f, 0.0f, 100.0f));

        Mouton::SpriteComponent* red = new Mouton::SpriteComponent("RedSprite");
        Mouton::SpriteComponent* green = new Mouton::SpriteComponent("GreenSprite");
        Mouton::PythonBehaviourComponent<Mouton::SpriteComponentScriptable>* behaviour =
            new Mouton::PythonBehaviourComponent<Mouton::SpriteComponentScriptable>("RedSpriteScript", "RedSpriteScript", red);
        Mouton::OrthographicCameraComponent* camera =
            new Mouton::OrthographicCameraComponent(
                "cameraComponent",
                cameraInstance);

        auto orthoBehaviour = new
            Mouton::PythonBehaviourComponent<Mouton::OrthographicCameraComponentScriptable>("CameraBehaviour", "CameraBehaviour", camera);

        m_Scene->AddComponent(Type::SpriteComponent, red);
        m_Scene->AddComponent(Type::SpriteComponent, green);
        m_Scene->AddComponent(Type::PythonBehaviourComponent, behaviour);
        m_Scene->AddComponent(Type::OrthographicCamera, camera);
        m_Scene->AddComponent(Type::PythonBehaviourComponent, orthoBehaviour);
        m_Scene->AddComponentToEntity("RedQuad", Type::SpriteComponent, "RedSprite");
        m_Scene->AddComponentToEntity("RedQuad", Type::PythonBehaviourComponent, "RedSpriteScript");
        m_Scene->AddComponentToEntity("GreenQuad", Type::SpriteComponent, "GreenSprite");
        m_Scene->AddComponentToEntity("RedQuad", Type::OrthographicCamera, "cameraComponent");
        m_Scene->AddComponentToEntity("RedQuad", Type::PythonBehaviourComponent, "CameraBehaviour");
    }
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

    ImGui::Begin("Console");

    auto freeSpace = ImGui::GetContentRegionAvail();

    freeSpace.x /= 3;
    freeSpace.y /= 4;

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
    }

    ImGui::SameLine();

    if(ImGui::Button("Pause scene", freeSpace))
    {
        if(m_ScenePlaying == SceneStates::Playing)
        {
            m_ScenePlaying = SceneStates::Paused;
            OnScenePause();
        }
    }

    ImGui::SameLine();

    if(ImGui::Button("Stop Scene", freeSpace))
    {
        if(m_ScenePlaying == SceneStates::Paused || m_ScenePlaying == SceneStates::Playing)
        {
            m_ScenePlaying = SceneStates::Stopped;
            OnSceneStop();
        }
    }

    ImGui::End();

    if(m_ScenePlaying == SceneStates::Playing)
        OnSceneUpdate(delta);

    // Does ImGui calls for the Scene explorer
    m_SceneExplorer.ShowSceneExplorer(m_Scene);
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
}

void EditorLayer::OnSceneStart()
{
    Mouton::PythonScriptEngine::Init();
    MTN_TRACE("Scene Started");

    m_Scene->ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);

            if(behaviour.pythonBehaviour->GetBoundComponent())
                behaviour.pythonBehaviour->OnSceneBegin();
    });
}

void EditorLayer::OnSceneUpdate(Mouton::Timestep delta)
{
    m_Scene->ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [delta](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);

            if(behaviour.pythonBehaviour->GetBoundComponent())
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

    m_Scene->ForEachComponents(Mouton::Component::ComponentType::PythonBehaviourComponent,
        [](Mouton::Component& comp) {
            auto& behaviour = Mouton::PythonBehaviourComponent<Mouton::PythonBinder>::ToPythonBehaviourComponent(comp);

            if(behaviour.pythonBehaviour->GetBoundComponent())
                behaviour.pythonBehaviour->OnSceneEnd();
        });
    Mouton::PythonScriptEngine::Stop();
}

EditorLayer::~EditorLayer()
{
    if(m_ScenePlaying == SceneStates::Paused || m_ScenePlaying == SceneStates::Playing)
        Mouton::PythonScriptEngine::Stop();
}
