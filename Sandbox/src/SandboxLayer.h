#include "Renderer/Layer.h"

#include "Core/Events/Events.h"

#include "Renderer/Model.h"
#include "Renderer/Camera.h"
#include "Ecs/Scene.h"
#include "MoutonComponents/SpriteComponent.h"
#include "Scripting/PythonBehaviourBinder.h"

class SandboxLayer : public Mouton::Layer
{
public:
    SandboxLayer();
    ~SandboxLayer();

    virtual void OnBind() override;
    virtual void OnUpdate(Mouton::Timestep delta) override;
    virtual void OnUnbind() override;
    virtual bool OnEvent(Mouton::Event& event) override;

private:
        std::shared_ptr<Mouton::Model> m_Model;
        Mouton::OrthographicCamera m_Camera;
        Mouton::Scene m_Scene;
        Mouton::PythonBinder* m_PythonComponentBehaviour;
};