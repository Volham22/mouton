#include "RendererContext.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Mouton
{
    RendererContext RendererContext::s_Instance;

    void RendererContext::InitContext(GraphicAPI api)
    {
        switch (api)
        {
        case GraphicAPI::OpenGL:
            MTN_INFO("Using OpenGL")
            MTN_INFO(OpenGLGraphicContext().GetGraphicContext());
            break;

        case GraphicAPI::None:
            MTN_ERROR("None GraphicAPI is being used !!");
            break;

        default:
            MTN_ERROR("Unknown GraphicAPI !!");
            break;
        }

        s_Instance = RendererContext(api);
    }

    std::unique_ptr<GraphicContext> RendererContext::GetCurrentGraphicContext()
    {
        return std::unique_ptr<OpenGLGraphicContext>(new OpenGLGraphicContext());
    }

    void RendererContext::DestroyContext()
    {
        MTN_INFO("Cleaning Graphic context ...");
        // Some stuff here
    }

    RendererContext::RendererContext()
        : m_API(GraphicAPI::None)
    {
    }

    RendererContext::RendererContext(GraphicAPI api)
        : m_API(api)
    {
    }


} // namespace Mouton
