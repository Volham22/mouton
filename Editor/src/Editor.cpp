#include "Engine.h"
MOUTON_CORE_INCLUDED
#include <cstdio>

#include "EditorLayer.h"

int main()
{
    printf("-- MOUTON Sandbox application --\n");

    Mouton::Application::InitApplication();

    EditorLayer* editorLayer = new EditorLayer();

    Mouton::Application::PushLayer(editorLayer);
    Mouton::Application::Run();
    Mouton::Application::EndApplication();

    delete editorLayer;

    return 0;
}
