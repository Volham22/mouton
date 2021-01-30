#ifndef MOUTON_IMGUILAYER_H
#define MOUTON_IMGUILAYER_H

#include "Renderer/Layer.h"

struct GLFWwindow;

namespace Mouton
{

    class ImGUILayer : public Layer
    {
    public:
        ImGUILayer(void* win, const char* name = "ImguiLayer");
        ~ImGUILayer();
        virtual void OnBind() override;
        virtual void OnUpdate(Timestep delta) override;
        virtual void OnRender() override;
        virtual void OnUnbind() override;
        virtual bool OnEvent(Event& event) override;

    private:
        GLFWwindow* m_WindowInstance;
    };

} // namespace Mouton

#endif
