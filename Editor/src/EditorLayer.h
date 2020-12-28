#include "Renderer/Layer.h"

#include "Core/Events/Events.h"

#include "Renderer/Camera.h"
#include "Renderer/Framebuffer.h"

#include "Ecs/Scene.h"

#include "SceneExplorer.h"

class EditorLayer : public Mouton::Layer
{
public:
    EditorLayer();
    ~EditorLayer();

    virtual void OnBind() override;
    virtual void OnUpdate(Mouton::Timestep delta) override;
    virtual void OnUnbind() override;
    virtual bool OnEvent(Mouton::Event& event) override;

    void SetScene(std::shared_ptr<Mouton::Scene>& scene);

private:
    std::shared_ptr<Mouton::Framebuffer> m_ViewportFramebuffer;
    Mouton::OrthographicCamera m_Camera;
    std::shared_ptr<Mouton::Scene> m_Scene;
    Mouton::Component* m_ComponentShown;
    SceneExplorer m_SceneExplorer;

    void ShowProperties();
};