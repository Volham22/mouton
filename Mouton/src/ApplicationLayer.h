#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include "Renderer/Layer.h" // Also include MoutonPch.h

namespace Mouton
{

    class RenderLayer : public Layer
    {
    public:
        RenderLayer(const char* name = "RenderLayer");
        virtual void OnBind() override;
        virtual void OnUpdate() override;
        virtual void OnUnbind() override;
        virtual bool OnEvent(Event& event) override;
    };

} // namespace Mouton


#endif