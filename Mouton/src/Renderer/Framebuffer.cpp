#include "Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "RendererContext.h"

namespace Mouton {

    std::shared_ptr<Framebuffer> Framebuffer::CreateFramebuffer()
    {
        switch (RendererContext::GetCurrentAPI())
        {
        case GraphicAPI::OpenGL:
            return std::make_shared<OpenGLFramebuffer>();

        case GraphicAPI::None:
            MTN_ERROR("None graphic API framebuffer are not supported !");
            return nullptr;

        default:
            MTN_ERROR("Unknown Framebuffer implementation. Graphic API is "
                      "probably not set.");
            return nullptr;
        }
    }

} // namespace Mouton
