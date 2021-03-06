#include "Engine.h"

#include "Core/Inputs.h"
#include "Core/Timestep.h"

namespace Mouton {

    Application::Application(const WindowProperties& properties)
        : m_WindowInstance(Window::CreateWindowInstance(properties)),
          m_LayerManager(),
          m_ImGuiLayer(m_WindowInstance->GetWindowInternalInstance()),
          m_WindowShouldClose(false)
    {
        Inputs::InitInputs(m_WindowInstance->GetWindowInternalInstance());
    }

    void Application::InitApplication()
    {
        Log::Init();
        s_Application = new Application(WindowProperties(1280, 720));
        s_Application->OnInit();
    }

    void Application::PushLayer(Layer* layer)
    {
        s_Application->PushLayerImpl(layer);
    }

    void Application::Run() { s_Application->RunImpl(); }

    bool Application::ApplicationShouldStop()
    {
        return s_Application->GetWindowShouldCloseImpl();
    }

    void Application::SetApplicationShouldStop(bool state)
    {
        s_Application->SetWindowShouldCloseImpl(state);
    }

    void Application::EndApplication() { delete s_Application; }

    void Application::OnInit()
    {
        using namespace std::placeholders;

        MTN_INFO("Begin of Mouton");
        m_WindowInstance->SetEventFunction(
            std::bind<bool>(&Application::OnEvent, this, _1));
    }

    bool Application::OnEvent(Event& event)
    {
        m_LayerManager.OnLayersEvent(event);
        return true;
    }

    void Application::RunImpl()
    {
        // Main Mouton Application Loop
        // ImGUi layer is always on the top
        while (!m_WindowShouldClose)
        {
            m_ImGuiLayer.OnBind();
            m_ImGuiLayer.OnUpdate(Timestep());
            m_LayerManager.UpdateLayers();
            m_ImGuiLayer.OnUnbind();
            m_WindowInstance->OnUpdate();
        }
    }

    void Application::PushLayerImpl(Layer* layer)
    {
        m_LayerManager.AddLayer(layer);
    }
} // namespace Mouton
