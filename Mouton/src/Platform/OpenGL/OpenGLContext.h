#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include "Renderer/GraphicContext.h"

namespace Mouton {

    class OpenGLGraphicContext : public GraphicContext
    {
      public:
        virtual const char* GetGraphicContext() override;
        virtual const char* GetGraphicApiVersion() override;
        virtual const char* GetRendererName() override;
    };

} // namespace Mouton

#endif