#ifndef PYTHON_SCRIPT_ENGINE_H
#define PYTHON_SCRIPT_ENGINE_H

#include "MoutonPch.h"

namespace Mouton
{

    class PythonScriptEngine
    {
    public:
        static void Init();
        static void Restart();
        static void Stop();
    };

} // namespace Mouton


#endif