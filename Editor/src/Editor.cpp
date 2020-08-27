#include "Engine.h"
MOUTON_CORE_INCLUDED
#include <cstdio>

#include "EditorLayer.h"

int main()
{
    printf("-- MOUTON Editor --\n");

    Mouton::Application::InitApplication();

    // No need to manually free the memory the Application will do it
    EditorLayer* editorLayer = new EditorLayer();

    Mouton::Application::PushLayer(editorLayer);
    Mouton::Application::Run();
    Mouton::Application::EndApplication();

    return 0;
}
