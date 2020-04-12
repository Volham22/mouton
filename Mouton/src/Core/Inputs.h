#ifndef INPUTS_H
#define INPUTS_H

#include "Core/MoutonCore.h"
#include "MoutonPch.h"

#if defined(MTN_PLATFORM_LINUX) || defined(MTN_PLATFORM_WIN)
#include "Platform/Keycodes.h"
#endif

namespace Mouton
{

    class Inputs
    {
    public:
        static void InitInputs(void* internalWindowInstance);
        static bool IsKeyPressed(int keycode);

    protected:
        virtual bool IsKeyPressedInt(int keycode) = 0;
    
    private:
        static std::unique_ptr<Inputs> s_InputInstance;
    };

} // namespace Mouton


#endif