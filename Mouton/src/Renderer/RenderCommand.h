#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "MoutonPch.h"

namespace Mouton {

    class RenderCommand
    {
      public:
        static void Init();
        static void Clear();
        static void SetDepthTest(bool enable = true);
        static void SetClearColor(const glm::vec4& color);
        static void SetBlending(bool enable = true);
        static void Draw(int count);
        static void DrawIndexed(int indicesCount);
        static void SetDebugMessage();

      protected:
        virtual void ClearImp() = 0;
        virtual void SetDepthTestImp(bool enable = true) = 0;
        virtual void SetClearColorImp(const glm::vec4& color) = 0;
        virtual void SetDebugMessageImpl() = 0;
        virtual void SetBlendingImpl(bool enable = true) = 0;
        virtual void DrawImp(int count) = 0;
        virtual void DrawIndexedImp(int indicesCount) = 0;

      private:
        static std::unique_ptr<RenderCommand> s_RenderCommand;
    };

} // namespace Mouton

#endif