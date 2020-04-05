#ifndef ENGINE_H
#define ENGINE_H

#include "MoutonCore.h"

#define MOUTON_CORE_INCLUDED Mouton::Application* Mouton::Application::s_Application;

namespace Mouton
{
    
    class Application
    {
    public:
        Application(Application &app) = delete;
        static void InitApplication();
        static void EndApplication();

    private:
        Application();
        void Run();

    private:
        static Application* s_Application;
    };
    
}

#endif
