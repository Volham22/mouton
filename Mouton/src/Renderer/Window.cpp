#include "Window.h"

#include "Platform/GLFWWindow.h"
#include "Core/MoutonCore.h"

namespace Mouton
{
    std::unique_ptr<Window> Window::CreateWindow(const WindowProperties& properties)
    {
        #if defined(MTN_PLATFORM_LINUX) || defined(MTN_PLATFORM_WIN)
        return std::unique_ptr<Window>(new GLFWWindowInstance(properties));
        #else
        #warning No Window instance supported on your hardware !
        MTN_FATAL("No Window instance supported on your hardware !");
        #endif
    }

} // namespace Mouton
