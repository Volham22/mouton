#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRenderCommand.h"
#include "RendererContext.h"

namespace Mouton
{

    std::unique_ptr<RenderCommand> RenderCommand::s_RenderCommand;

    void RenderCommand::Init()
    {
        switch(RendererContext::GetCurrentAPI())
        {
        case GraphicAPI::OpenGL:
            s_RenderCommand = std::make_unique<OpenGLRenderCommand>();
            break;
        
        case GraphicAPI::None:
            MTN_WARN("None grahpic API render command are not allowed !");
            break;
        
        default:
            MTN_WARN("Unknown graphic API for RenderCommand !");
            break;
        }
    }

    void RenderCommand::Clear()
    {
        s_RenderCommand->ClearImp();
    }

    void RenderCommand::SetClearColor(const glm::vec4& color)
    {
        s_RenderCommand->SetClearColorImp(color);
    }

    void RenderCommand::Draw(int count)
    {
        s_RenderCommand->DrawImp(count);
    }

    void RenderCommand::DrawIndexed(int indicesCount)
    {
        s_RenderCommand->DrawIndexedImp(indicesCount);
    }

} // namespace Mouton
