#include "Texture.h"

#include "Renderer/RendererContext.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Mouton
{

    std::shared_ptr<Texture2D> Texture2D::CreateTexture(const char* filepath)
    {
        switch (RendererContext::GetCurrentAPI())
        {
        case GraphicAPI::OpenGL:
            return std::make_shared<OpenGLTexture2D>(filepath);
        
        case GraphicAPI::None:
            MTN_WARN("None graphic API Texture2D creation is not allowed !");
            return nullptr;
        
        default:
            MTN_WARN("Unknown graphic API for Texture2D creation !");
            return nullptr;
        }
    }

} // namespace Mouton
