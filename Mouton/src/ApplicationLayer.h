#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include "Renderer/Layer.h" // Also include MoutonPch.h

struct GLFWwindow;

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

    class ImGUILayer : public Layer
    {
    public:
        ImGUILayer(void* win, const char* name = "ImguiLayer");
        ~ImGUILayer();
        virtual void OnBind() override;
        virtual void OnUpdate() override;
        virtual void OnUnbind() override;
        virtual bool OnEvent(Event& event) override;

    private:
        GLFWwindow* m_WindowInstance;
    };

} // namespace Mouton


#endif