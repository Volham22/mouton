#include "VertexArray.h"

#include "RendererContext.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Mouton
{

    std::shared_ptr<VertexArray> VertexArray::CreateVertexArray()
    {
        switch(RendererContext::GetCurrentAPI())
        {
        case GraphicAPI::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        
        case GraphicAPI::None:
            MTN_WARN("None Vertex Array are not allowed !");
            return nullptr;
        
        default:
            MTN_WARN("Unknown Vertex Array graphic API !");
            return nullptr;
        }
    }

} // namespace Mouton
