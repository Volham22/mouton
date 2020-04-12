#include "Engine.h"

#include "Core/Inputs.h"

namespace Mouton
{

    Application::Application(const WindowProperties& properties)
        : m_WindowInstance(Window::CreateWindowInstance(properties))
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

            EventSystem::ApplyFunction<KeyPressedEvent>(&event, [](Event& event) -> bool {
                auto& ev = dynamic_cast<KeyPressedEvent&>(event);

                if(ev.GetCode() == Keys::SPACE)
                    MTN_INFO("Space key pressed !");
                
                return true;
            });

            EventSystem::ApplyFunction<KeyMaintainedEvent>(&event, [](Event& event) -> bool {
                auto& ev = dynamic_cast<KeyMaintainedEvent&>(event);

                if(ev.GetCode() == Keys::SPACE)
                    MTN_INFO("Space key maintained !");

                return true;
            });

            EventSystem::ApplyFunction<KeyReleasedEvent>(&event, [](Event& event) -> bool {
                auto& ev = dynamic_cast<KeyReleasedEvent&>(event);

                if(ev.GetCode() == Keys::SPACE)
                    MTN_INFO("Space key released !");

                return true;
            });

            EventSystem::ApplyFunction<MouseButtonPressedEvent>(&event, [](Event& event) -> bool {
                auto& ev = dynamic_cast<MouseButtonPressedEvent&>(event);

                if(ev.GetCode() == Keys::MOUSE1)
                    MTN_INFO("Left button pressed !");

                return true;
            });

            EventSystem::ApplyFunction<MouseButtonMaintainedEvent>(&event, [](Event& event) -> bool {
                auto& ev = dynamic_cast<MouseButtonMaintainedEvent&>(event);

                if(ev.GetCode() == Keys::MOUSE1)
                    MTN_INFO("Left button maintained !");

                return true;
            });

            EventSystem::ApplyFunction<MouseButtonReleasedEvent>(&event, [](Event& event) -> bool {
                auto& ev = dynamic_cast<MouseButtonReleasedEvent&>(event);

                if(ev.GetCode() == Keys::MOUSE1)
                    MTN_INFO("Left button released !");

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
