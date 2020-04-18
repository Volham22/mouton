#include "Renderer.h"

#include "RenderCommand.h"

namespace Mouton
{

    void Renderer::InitRenderer()
    {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(const glm::vec4& color)
    {
        // Retrieve here projection and camera matrix
        RenderCommand::SetClearColor(color);
        RenderCommand::Clear();
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
