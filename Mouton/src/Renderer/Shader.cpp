#include "Shader.h"

#include "RendererContext.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Mouton
{

    std::shared_ptr<Shader> Shader::CreateShader(const std::string& filepath)
    {
        switch(RendererContext::GetCurrentAPI())
        {
        case GraphicAPI::OpenGL:
            return std::make_shared<OpenGLShader>(filepath);
        
        case GraphicAPI::None:
            MTN_WARN("None Graphic API shaders are not allowed !");
            return nullptr;
        
        default:
            MTN_WARN("Unknown Graphic API Shader not allowed !");
            return nullptr;
        }
    }

} // namespace Mouton
