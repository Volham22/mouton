#include "SandboxLayer.h"
#include "imgui.h"

#include "Engine.h"

#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/RendererContext.h"

using namespace Mouton;

SandboxLayer::SandboxLayer()
    : Layer("Sandbox Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene()
{
    RendererContext::InitContext(GraphicAPI::OpenGL);
    Renderer::InitRenderer();
    Renderer2D::Init();
}

void SandboxLayer::OnBind()
{
    // m_PythonComponentBehaviour->OnSceneBegin();
}

void SandboxLayer::OnUnbind()
{
    // m_PythonComponentBehaviour->OnSceneEnd();
}

void SandboxLayer::OnUpdate(Timestep delta)
{
    // m_PythonComponentBehaviour->OnSceneUpdate(delta);

    static int count = 100;

    Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());
    for (int i = 0; i < count; i += 20)
    {
        for (int j = 0; j < count; j += 20)
            Renderer2D::DrawQuad({ 10.0f + i, 10.0f + j, 0.0f },
                                 { 10.0f, 10.0f }, { 1.0f, 0.0f, 0.75f, 1.0f });
    }
    Renderer2D::EndScene();

    ImGui::Begin("Debug Performance window");
    ImGui::Text("Mouton Performance.");
    ImGui::Text(
        (std::to_string(Renderer2D::GetDrawCallPerFrame()) + " drawcalls")
            .c_str());
    ImGui::SliderInt("Count", &count, 10, 10000);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void SandboxLayer::OnRender()
{}

bool SandboxLayer::OnEvent(Event& event)
{
    EventSystem::ApplyFunction<WindowCloseEvent>(
        &event, [](Event& event) -> bool {
            MTN_TRACE("On window close ...");
            Application::SetApplicationShouldStop(true);
            return true;
        });

    EventSystem::ApplyFunction<MouseButtonPressedEvent>(
        &event, [](Event& event) -> bool {
            MTN_TRACE("Mouse Button pressed !");

            return true;
        });

    return event.Handled();
}

SandboxLayer::~SandboxLayer()
{
    RendererContext::DestroyContext();
}