#include "OpenGLContext.h"

#include <glad/glad.h>

namespace Mouton {

    const char* OpenGLGraphicContext::GetGraphicContext()
    {
        std::string res = "Version: ";

        res += (char*)glGetString(GL_VERSION);
        res += "\n\tRenderer: ";
        res += (char*)glGetString(GL_RENDERER);
        res += "\n\tGLSL Version: ";
        res += (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
        res += '\n';

        return res.c_str();
    }

    const char* OpenGLGraphicContext::GetGraphicApiVersion()
    {
        return (const char*)glGetString(GL_VERSION);
    }

    const char* OpenGLGraphicContext::GetRendererName()
    {
        return (const char*)glGetString(GL_RENDERER);
    }

} // namespace Mouton
