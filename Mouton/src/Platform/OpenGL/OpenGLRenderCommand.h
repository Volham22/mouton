#ifndef OPENGL_RENDER_COMMAND_H
#define OPENGL_RENDER_COMMAND_H

#include "Renderer/RenderCommand.h"

namespace Mouton {

    class OpenGLRenderCommand : public RenderCommand
    {
      protected:
        virtual void ClearImp() override;
        virtual void SetClearColorImp(const glm::vec4& color);
        virtual void SetDepthTestImp(bool enable) override;
        virtual void SetBlendingImpl(bool enable = true) override;
        virtual void SetDebugMessageImpl() override;
        virtual void DrawImp(int count) override;
        virtual void DrawIndexedImp(int indicesCount) override;
    };

} // namespace Mouton

#endif