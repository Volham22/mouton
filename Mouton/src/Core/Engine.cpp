#include "Engine.h"

namespace Mouton
{

    Application::Application()
    {

    }


    void Application::InitApplication()
    {
        s_Application = new Application();
        s_Application->OnInit();
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
    }

    void Application::Run()
    {
        // Main Mouton Application Loop
        while(true);
    }
}
