#include "SandboxLayer.h"
#include "imgui.h"

#include "Renderer/RendererContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

#include "MoutonComponents/SpriteComponent.h"
#include "Scripting/PythonScriptEngine.h"

using namespace Mouton;

SandboxLayer::SandboxLayer()
    : Layer("Sandbox Layer"), m_Camera(0.0f, 100.0f, 0.0f, 100.0f), m_Scene(),
      m_PythonComponentBehaviour(nullptr)
{
    RendererContext::InitContext(GraphicAPI::OpenGL);
    Renderer::InitRenderer();
    Renderer2D::Init();

    PythonScriptEngine::Init();

    m_PythonComponentBehaviour = new SpriteComponentScriptable("myComp", new SpriteComponent("myComp"));
}

void SandboxLayer::OnBind()
{
    m_PythonComponentBehaviour->OnSceneBegin();
}

void SandboxLayer::OnUnbind()
{
    m_PythonComponentBehaviour->OnSceneEnd();
}

void SandboxLayer::OnUpdate()
{
    m_PythonComponentBehaviour->OnSceneUpdate();

    Renderer2D::BeginScene(m_Camera.GetViewProjectionMatrix());
    for (int i = 0; i < 100; i += 20)
    {
        for (int j = 0; j < 100; j += 20)
            Renderer2D::DrawQuad({10.0f + i, 10.0f + j, 0.0f}, {10.0f, 10.0f}, {1.0f, 0.0f, 0.75f, 1.0f});
    }
    Renderer2D::EndScene();
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
    delete m_PythonComponentBehaviour;
    PythonScriptEngine::Stop();
}