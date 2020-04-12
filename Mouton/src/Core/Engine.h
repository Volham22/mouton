#ifndef ENGINE_H
#define ENGINE_H

#include "MoutonCore.h"

#include "Renderer/Window.h"

#define MOUTON_CORE_INCLUDED Mouton::Application* Mouton::Application::s_Application;

namespace Mouton
{
    
    class Application
    {
    public:
        Application(const WindowProperties& properties);
        Application(Application &app) = delete;
        static void InitApplication();
        static void EndApplication();

    private:
        Application();
        void OnInit();
        void Run();
        bool OnEvent(Event& event);

    private:
        static Application* s_Application;
        std::unique_ptr<Window> m_WindowInstance;
    };
    
}

#endif
