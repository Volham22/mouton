#ifndef RENDERER_H
#define RENDERER_H

#include "MoutonPch.h"

namespace Mouton {
    class Renderer
    {
      public:
        static void InitRenderer();
        static void BeginScene(const glm::vec4& clearColor
                               = { 0.2f, 0.2f, 0.2f, 1.0f });
        static void SetDepthTest(bool enable);
        static void SetBlending(bool enable);
        static void Draw(int count); // Everything must be bound correctly
        static void DrawIndexed(int indicesCount);
        static void EndScene();
    };

} // namespace Mouton

#endif