#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "MoutonPch.h"

namespace Mouton
{

    class RenderCommand
    {
    public:
        static void Init();
        static void Clear();
        static void SetClearColor(const glm::vec4& color);
        static void Draw(int count);
        static void DrawIndexed(int indicesCount);
    
    protected:
        virtual void ClearImp() = 0;
        virtual void SetClearColorImp(const glm::vec4& color) = 0;
        virtual void DrawImp(int count) = 0;
        virtual void DrawIndexedImp(int indicesCount) = 0;

    private:
        static std::unique_ptr<RenderCommand> s_RenderCommand;
    };

} // namespace Mouton


#endif