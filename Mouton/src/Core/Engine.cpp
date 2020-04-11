#include "Engine.h"

namespace Mouton
{

    Application::Application(const WindowProperties& properties)
        : m_WindowInstance(Window::CreateWindowInstance(properties))
    {

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
        MTN_INFO("Begin of Mouton");

        using namespace std::placeholders;

        m_WindowInstance->SetEventFunction([](Event& event) -> bool {
            EventSystem::ApplyFunction<WindowCloseEvent>(&event, [](Event& event) -> bool {
                MTN_INFO("On window close ...");
                return true;
            });

            EventSystem::ApplyFunction<WindowFocusEvent>(&event, [](Event& event) -> bool {
                MTN_INFO("On window focus");
                return true;
            });

            EventSystem::ApplyFunction<WindowLostFocusEvent>(&event, [](Event& event) -> bool {
                MTN_INFO("Window lost focus");
                return true;
            });

            EventSystem::ApplyFunction<WindowMovedEvent>(&event, [](Event& event) -> bool {
                auto& ev = dynamic_cast<WindowMovedEvent&>(event);
                MTN_TRACE("On window move");
                return true;
            });

            EventSystem::ApplyFunction<WindowMinimizedEvent>(&event, [](Event & event) -> bool {
                MTN_INFO("On window minimize");

                return true;
            });

            EventSystem::ApplyFunction<WindowResizeEvent>(&event, [](Event& event) -> bool {
                MTN_INFO("On window resize")
                return true;
            });

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
