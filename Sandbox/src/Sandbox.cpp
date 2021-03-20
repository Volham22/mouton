#include "Engine.h"
MOUTON_CORE_INCLUDED
#include <cstdio>

#include "SandboxLayer.h"

int main()
{
    printf("-- MOUTON Sandbox application --\n");

    Mouton::Application::InitApplication();

    SandboxLayer* sandboxLayer = new SandboxLayer();

    Mouton::Application::PushLayer(sandboxLayer);
    Mouton::Application::Run();
    Mouton::Application::EndApplication();
}
