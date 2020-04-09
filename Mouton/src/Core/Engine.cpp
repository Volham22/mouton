#include "Engine.h"

namespace Mouton
{

    Application::Application(const WindowProperties& properties)
        : m_WindowInstance(Window::CreateWindow(properties))
    {

    }


    void Application::InitApplication()
    {
        s_Application->OnInit();
        s_Application = new Application(WindowProperties(1280, 720));
        s_Application->Run();
    }

    void Application::EndApplication()
    {
        delete s_Application;
    }

    void Application::OnInit()
    {
        Log::Init();
        MTN_INFO("Begin of Mouton");

        ApplicationEvent appEv;
        EventSystem::ApplyFunction<ApplicationEvent>(&appEv, [](Event& e) -> bool {
            MTN_TRACE("Event works !");
            return true;
        });
    }

    void Application::Run()
    {
        // Main Mouton Application Loop
        while(true)
        {
            m_WindowInstance->OnUpdate();
        }
    }
}
