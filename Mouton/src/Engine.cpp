#include "Engine.h"

#include "Core/Inputs.h"
#include "ApplicationLayer.h"

namespace Mouton
{

    Application::Application(const WindowProperties& properties)
        : m_WindowInstance(Window::CreateWindowInstance(properties)), m_LayerManager()
    {
        Inputs::InitInputs(m_WindowInstance->GetWindowInternalInstance());
    }


    void Application::InitApplication()
    {
        Log::Init();
        s_Application = new Application(WindowProperties(1280, 720));
        s_Application->OnInit();
        s_Application->Run();
    }

    void Application::EndApplication()
    {
        delete s_Application;
    }

    void Application::OnInit()
    {
        using namespace std::placeholders;

        MTN_INFO("Begin of Mouton");
        m_WindowInstance->SetEventFunction(std::bind<bool>(&Application::OnEvent, this, _1));

        m_LayerManager.AddLayer(new RenderLayer());
    }

    bool Application::OnEvent(Event& event)
    { 
        m_LayerManager.OnLayersEvent(event);
        return true;
    }

    void Application::Run()
    {
        // Main Mouton Application Loop
        while(true)
        {
            m_LayerManager.UpdateLayers();
            m_WindowInstance->OnUpdate();
        }
    }
}
