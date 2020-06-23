#include "Renderer/Layer.h"

#include "Core/Events/Events.h"

#include "Renderer/Model.h"
#include "Renderer/Camera.h"

class SandboxLayer : public Mouton::Layer
{
public:
    SandboxLayer();

    virtual void OnBind() override;
    virtual void OnUpdate() override;
    virtual void OnUnbind() override;
    virtual bool OnEvent(Mouton::Event& event) override;

private:
        std::shared_ptr<Mouton::Model> m_Model;
        Mouton::OrthographicCamera m_Camera;
};