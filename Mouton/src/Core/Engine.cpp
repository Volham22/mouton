#include "Engine.h"

namespace Mouton
{

    Application::Application()
    {

    }


    void Application::InitApplication()
    {
        s_Application = new Application();
        s_Application->Run();
    }

    void Application::EndApplication()
    {
        delete s_Application;
    }

    void Application::Run()
    {
        // Main Mouton Application Loop
    }
}
