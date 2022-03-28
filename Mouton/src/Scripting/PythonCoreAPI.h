#ifndef PYTHON_CORE_API_H
#define PYTHON_CORE_API_H

#include "MoutonPch.h"

namespace Mouton::PythonAPI {

    class Core
    {
      public:
        static void Print(const std::string& message);
    };

} // namespace Mouton::PythonAPI

#endif