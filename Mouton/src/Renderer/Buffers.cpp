#include "Buffers.h"

#include "RendererContext.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

namespace Mouton
{

    std::shared_ptr<VertexBuffer> VertexBuffer::CreateVertexBuffer()
    {
        switch(RendererContext::GetCurrentAPI())
        {
        case GraphicAPI::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>();
            break;
        
        default:
            MTN_ERROR("Unkown VertexBuffer implementation !!\nGraphicAPI is propably not set.");
            return nullptr;
        }
    }

} // namespace Mouton
