#include "Inputs.h"

#include "Core/MoutonCore.h"
#include "Platform/GLFWInputs.h"

namespace Mouton
{

    std::unique_ptr<Inputs> Inputs::s_InputInstance;

    void Inputs::InitInputs(void* internalWindowInstance)
    {
        #if defined(MTN_PLATFORM_LINUX) || defined(MTN_PLATFORM_WIN)
        s_InputInstance =
            std::unique_ptr<GLFWInputs>(new GLFWInputs(static_cast<GLFWwindow*>(internalWindowInstance)));
        #else
            #warning No inputs handling available on your platform (maybe Window too)
        #endif
    }

    bool Inputs::IsKeyPressed(int keyCode)
    {
        return s_InputInstance->IsKeyPressedInt(keyCode);
    }

} // namespace Mouton
