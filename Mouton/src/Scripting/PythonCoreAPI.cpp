#include "PythonCoreAPI.h"

namespace Mouton::PythonAPI {

    void Core::Print(const std::string& message)
    {
        MTN_TRACE("Python script: {}", message.c_str());
    }

} // namespace Mouton::PythonAPI
