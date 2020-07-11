#include "Renderer/Layer.h"

#include "Core/Events/Events.h"

#include "Renderer/Camera.h"
#include "Renderer/Framebuffer.h"

class EditorLayer : public Mouton::Layer
{
public:
    EditorLayer();

    virtual void OnBind() override;
    virtual void OnUpdate() override;
    virtual void OnUnbind() override;
    virtual bool OnEvent(Mouton::Event& event) override;

private:
        std::shared_ptr<Mouton::Framebuffer> m_ViewportFramebuffer;
        Mouton::OrthographicCamera m_Camera;
};