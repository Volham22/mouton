#ifndef RENDERER_CONTEXT_H

#include "MoutonPch.h"
#include "GraphicContext.h"

namespace Mouton
{
    enum class GraphicAPI : uint8_t {
        None = 0, OpenGL = 1 // Vulkan, DirectX 11, DirectX12 ...
    };

    class RendererContext
    {
    public:
        static void InitContext(GraphicAPI api);
        static void DestroyContext();
        static GraphicAPI GetCurrentAPI() { return s_Instance.GetCurrentAPIImp(); };
        static std::unique_ptr<GraphicContext> GetCurrentGraphicContext();

    private:
        RendererContext();
        RendererContext(GraphicAPI api);
        GraphicAPI GetCurrentAPIImp() const { return m_API; };

        static RendererContext s_Instance;
        GraphicAPI m_API;
    };

} // namespace Mouton


#endif