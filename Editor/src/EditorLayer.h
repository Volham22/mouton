#include "Renderer/Layer.h"

#include "Core/Events/Events.h"

#include "Renderer/Camera.h"
#include "Renderer/Framebuffer.h"

#include "Ecs/Scene.h"

#include "SceneExplorer.h"
#include "Logger.h"

class EditorLayer : public Mouton::Layer
{
public:
    EditorLayer();
    ~EditorLayer();

    virtual void OnBind() override;
    virtual void OnUpdate(Mouton::Timestep delta);
    virtual void OnRender() override;
    virtual void OnUnbind() override;
    virtual bool OnEvent(Mouton::Event& event) override;

    void SetScene(std::shared_ptr<Mouton::Scene>& scene);

private:
    enum class SceneStates {
        None = 0, Playing = 1, Paused = 2, Stopped = 3
    };

    std::shared_ptr<Mouton::Framebuffer> m_ViewportFramebuffer;
    Mouton::OrthographicCamera m_Camera;
    std::shared_ptr<Mouton::Scene> m_Scene;
    Mouton::Component* m_ComponentShown;
    SceneExplorer m_SceneExplorer;
    SceneStates m_ScenePlaying;
    Logger m_Logger;

private:
    void OnSceneStart();
    void OnSceneUpdate(Mouton::Timestep delta);
    void OnScenePause();
    void OnSceneResume();
    void OnSceneStop();

    void ShowProperties();

    Mouton::PythonBinder::ErrorCallback m_PythonErrorCb = [this](const std::exception& e) {
        const auto& str = std::string("Python Script Error: ") + e.what();
        m_Logger.AddLog(str.c_str());
    };
};
