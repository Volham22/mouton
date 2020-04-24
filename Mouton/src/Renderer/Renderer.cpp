#include "Renderer.h"

#include "RenderCommand.h"

namespace Mouton
{

    void Renderer::InitRenderer()
    {
        RenderCommand::Init();
        RenderCommand::SetDebugMessage();
    }

    void Renderer::BeginScene(const glm::vec4& color)
    {
        // Retrieve here projection and camera matrix
        RenderCommand::SetClearColor(color);
        RenderCommand::Clear();
    }

    void Renderer::SetDepthTest(bool enable)
    {
        RenderCommand::SetDepthTest(enable);
    }

    void Renderer::SetBlending(bool enable)
    {
        RenderCommand::SetBlending(true);
    }

    void Renderer::Draw(int count)
    {
        RenderCommand::Draw(count);
    }

    void Renderer::DrawIndexed(int indicesCount)
    {
        RenderCommand::DrawIndexed(indicesCount);
    }

    void Renderer::EndScene()
    {
        // Some stuff to clear our scene here
    }

} // namespace Mouton
