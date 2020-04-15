#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

#include "MoutonPch.h"

namespace Mouton
{

    class GraphicContext
    {
    public:
        virtual const char* GetGraphicContext() = 0;
        virtual const char* GetGraphicApiVersion() = 0;
        virtual const char* GetRendererName() = 0;
    };

} // namespace Mouton


#endif