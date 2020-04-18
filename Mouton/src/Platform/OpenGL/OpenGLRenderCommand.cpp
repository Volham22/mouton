#include "OpenGLRenderCommand.h"

#include <glad/glad.h>

namespace Mouton
{

    void OpenGLRenderCommand::ClearImp()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRenderCommand::SetClearColorImp(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderCommand::DrawImp(int count)
    {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void OpenGLRenderCommand::DrawIndexedImp(int indicesCount)
    {
        // EBO must be bound before !
        glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
    }

} // namespace Mouton
