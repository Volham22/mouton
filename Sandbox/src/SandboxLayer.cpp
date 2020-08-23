#include "SandboxLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"

#include "Renderer/Renderer2D.h"

using namespace Mouton;

SandboxLayer::SandboxLayer()
    : Layer("Sandbox Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene(),
      m_Vec2Behaviour(new glm::vec2(2.0, 42.0f))
{
    RendererContext::InitContext(GraphicAPI::OpenGL);
    Renderer::InitRenderer();
    Renderer2D::Init();

    MTN_ASSERT(false, "Ooops");

    m_Vec2Behaviour.SetOnSceneUpdate([](glm::vec2& vec) {
        vec.x += 0.01f;
        vec.y += 0.01f;

        MTN_TRACE("x: {0} y: {1}", vec.x, vec.y);
    });
}

void SandboxLayer::OnBind()
{

}

void SandboxLayer::OnUnbind()
{
}

void SandboxLayer::OnUpdate()
{
    Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());
    for (int i = 0; i < 100; i += 20)
    {
        for (int j = 0; j < 100; j += 20)
            Renderer2D::DrawQuad({10.0f + i, 10.0f + j, 0.0f}, {10.0f, 10.0f}, {1.0f, 0.0f, 0.75f, 1.0f});
    }
    Renderer2D::EndScene();

    m_Vec2Behaviour.DoUpdate();
}

bool SandboxLayer::OnEvent(Event &event)
{
    EventSystem::ApplyFunction<WindowCloseEvent>(&event, [](Event &event) -> bool {
        MTN_TRACE("On window close ...");
        return true;
    });

    EventSystem::ApplyFunction<MouseButtonPressedEvent>(&event, [](Event &event) -> bool {
        MTN_TRACE("Mouse Button pressed !");

        return true;
    });

    return event.Handled();
}

SandboxLayer::~SandboxLayer()
{
}