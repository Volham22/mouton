#include "EditorLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"

#include "Renderer/Renderer2D.h"

using namespace Mouton;

EditorLayer::EditorLayer()
    : Layer("Editor Layer"),
      m_Camera(0.0f, 100.0f, 0.0f, 100.0f)
{
    RendererContext::InitContext(GraphicAPI::OpenGL);
    Renderer::InitRenderer();
    Renderer2D::Init();

    m_ViewportFramebuffer = Framebuffer::CreateFramebuffer();
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
    m_ViewportFramebuffer->CreateBlankTexture(width, height);

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