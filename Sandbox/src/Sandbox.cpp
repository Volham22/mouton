#include "Core/Engine.h"
MOUTON_CORE_INCLUDED
#include <cstdio>


int main()
{
    printf("-- MOUTON Sandbox application --\n");

    Mouton::Application::InitApplication();
    Mouton::Application::EndApplication();
}
